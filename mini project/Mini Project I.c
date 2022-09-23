#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define MAXLEN 256
#define TBLSIZE 65535

/*
Something like Python
>> y = 2
>> z = 2
>> x = 3*y + 4/(2*z)

*/

/*
the only type: integer
everything is an expression
  statement   := END | expr END
  expr        := term expr_tail
  expr_tail   := ADDSUB term expr_tail | NIL
  term        := factor term_tail
  term_tail := MULDIV factor term_tail | NIL
  factor      := INT | ADDSUB INT | ADDSUB ID | ID ASSIGN expr | ID | LPAREN expr RPAREN
*/

typedef enum {UNKNOWN, END, INT, ID, ADDSUB, MULDIV, ASSIGN,
LPAREN, RPAREN, ENDFILE} TokenSet;

typedef enum {MISPAREN, NOTNUMID, NOTFOUND, RUNOUT} ErrorType;

typedef struct {
    char name[MAXLEN];
    int val;
} Symbol;
extern Symbol table[TBLSIZE];
Symbol table[TBLSIZE];
int sbcount = 3;

typedef struct _Node {
    char lexeme[MAXLEN];
    TokenSet data;
    int val;
    int mem;
    int reg;
    struct _Node *left, *right;
} BTNode;

extern void statement(void);
extern BTNode* expr(void);
extern BTNode* expr_tail(BTNode *left);
extern BTNode* term(void);
extern BTNode* term_tail(BTNode *left);
extern BTNode* factor(void);
extern char* getLexeme(void);
extern int match (TokenSet token);
extern void advance(void);
extern int getval(void);
extern BTNode* makeNode(TokenSet tok, const char *lexe);
extern void freeTree(BTNode *root);
extern void error(ErrorType errorNum);
extern void evaluateTree(BTNode *root);
static TokenSet getToken(void);
static TokenSet lookahead = UNKNOWN;
static char lexeme[MAXLEN];

int main()
{
    while (1) {
        statement();
    }

    return 0;
}

/*statement   := ENDFILE | END | expr END*/
void statement(void)
{
    BTNode* retp;

    if (match(ENDFILE)) {
    	printf("MOV r0 [0]\n");
		printf("MOV r1 [4]\n");
		printf("MOV r2 [8]\n");
    	printf("EXIT 0\n");
    	
        exit(0);
    } else if (match(END)) {
        advance();
    } else {
        retp = expr();
        if (match(END)) {
			evaluateTree(retp);
            freeTree(retp);

            advance();
        }
    }
}

/*  expr        := term expr_tail*/
BTNode* expr(void)
{
    BTNode *node;

    node = term();

    return expr_tail(node);
}

/*  expr_tail   := ADDSUB term expr_tail | NIL*/
BTNode* expr_tail(BTNode *left)
{
    BTNode *node;

    if (match(ADDSUB)) {
        node = makeNode(ADDSUB, getLexeme());
        advance();

        node->left = left;
        node->right = term();

        return expr_tail(node);
    }
    else
        return left;
}

/*  term        := factor term_tail*/
BTNode* term(void)
{
    BTNode *node;

    node = factor();

    return term_tail(node);
}

/*term_tail := MULDIV factor term_tail | NIL*/
BTNode* term_tail(BTNode *left)
{
    BTNode *node;

    if (match(MULDIV)) {
        node = makeNode(MULDIV, getLexeme());
        advance();

        node->left = left;
        node->right = factor();

        return term_tail(node);
    }
    else
        return left;
}

/*factor := INT | ADDSUB INT | ADDSUB ID | ID ASSIGN expr | ID | LPAREN expr RPAREN*/
BTNode* factor(void)
{
    BTNode* retp = NULL;
    char tmpstr[MAXLEN];

    if (match(INT)) {
        retp =  makeNode(INT, getLexeme());
        retp->val = getval();
        advance();
    } else if (match(ID)) {
        BTNode* left = makeNode(ID, getLexeme());
        left->val = getval();
        strcpy(tmpstr, getLexeme());
        advance();
        if (match(ASSIGN)) {
            retp = makeNode(ASSIGN, getLexeme());
            advance();
            retp->right = expr();
            retp->left = left;
        } else {
            retp = left;
        }
    } else if (match(ADDSUB)) {
        strcpy(tmpstr, getLexeme());
        advance();
        if (match(ID) || match(INT)) {
            retp = makeNode(ADDSUB, tmpstr);
            if (match(ID))
                retp->right = makeNode(ID, getLexeme());
            else
                retp->right = makeNode(INT, getLexeme());
            retp->right->val = getval();
            retp->left = makeNode(INT, "0");
            retp->left->val = 0;
            advance();
        } else {
            error(NOTNUMID);
        }
    } else if (match(LPAREN)) {
        advance();
        retp = expr();
        if (match(RPAREN)) {
            advance();
        } else {
            error(MISPAREN);
        }
    } else {
        error(NOTNUMID);
    }
    return retp;
}

char* getLexeme(void)
{
    return lexeme;
}

int match(TokenSet token)
{
    if (lookahead == UNKNOWN) advance();
    return token == lookahead;
}

void advance(void)
{
    lookahead = getToken();
}

TokenSet getToken(void)
{
    int i;
    char c;

    while ( (c = fgetc(stdin)) == ' ' || c== '\t' );  // 忽略空白字元

    if (isdigit(c)) {
        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;
        while (isdigit(c) && i<MAXLEN) {
            lexeme[i] = c;
            ++i;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return INT;
    } else if (c == '+' || c == '-' || c == '&' || c == '|' || c == '^') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return ADDSUB;
    } else if (c == '*' || c == '/') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return MULDIV;
    } else if (c == '\n') {
        lexeme[0] = '\0';
        return END;
    } else if (c == '=') {
        strcpy(lexeme, "=");
        return ASSIGN;
    } else if (c == '(') {
        strcpy(lexeme, "(");
        return LPAREN;
    } else if (c == ')') {
        strcpy(lexeme, ")");
        return RPAREN;
    } else if (isalpha(c) || c == '_') {
        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;
        while (isalpha(c) || isdigit(c) || c == '_') {
            lexeme[i] = c;
            ++i;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return ID;
    } else if (c == EOF) {
        return ENDFILE;
    } else {
        printf("EXIT 1");
        exit(0);
		//return UNKNOWN;
    }
}

int getval(void)
{
    int i, retval, found;

    if (match(INT)) {
        retval = atoi(getLexeme());
    } else if (match(ID)) {
        i = 3; found = 0; retval = 0;
        while (i<sbcount && !found) {
        	if (strcmp(getLexeme(), "x")==0 || strcmp(getLexeme(), "y")==0 || strcmp(getLexeme(), "z")==0){
				found = 1;
				break;
			} 
            if (strcmp(getLexeme(), table[i].name)==0) {
                retval = table[i].val;
                found = 1;
                break;
            } else {
                i++;
            }
        }
        if (!found) {
            if (sbcount < TBLSIZE) {
                strcpy(table[sbcount].name, getLexeme());
                table[sbcount].val = 0;
                sbcount++;
            } else {
                error(RUNOUT);
            }
        }
    }
    return retval;
}

/* create a node without any child.*/
BTNode* makeNode(TokenSet tok, const char *lexe){
    BTNode *node = (BTNode*) malloc(sizeof(BTNode));
    strcpy(node->lexeme, lexe);
    node->data = tok;
    node->val = 0;
    if(node->lexeme[0]=='x' && node->lexeme[1]=='\0') node->mem = 0;
    else if(node->lexeme[0]=='y' && node->lexeme[1]=='\0') node->mem = 4;
    else if(node->lexeme[0]=='z' && node->lexeme[1]=='\0') node->mem = 8;
    else node->mem = -1;
    node->reg = -1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

/* clean a tree.*/
void freeTree(BTNode *root){
    if (root!=NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

void error(ErrorType errorNum)
{
    switch (errorNum) {
    case MISPAREN:
    case NOTNUMID:
    case NOTFOUND:
    case RUNOUT:
        printf("EXIT 1");
    }
    exit(0);
}

void evaluateTree(BTNode *root)
{
    static reg = 0, mem = 12, leftmem = -1, flag = -1;
    if (root != NULL)
    {
        if(flag==-1 && (strcmp(root->lexeme, "=")!=0)){
        	printf("EXIT 1");
        	exit(0);
		}
		flag = 1;
		switch (root->data)
        {
        case ID:
        	if(leftmem==-1){ //flag=0在等號左邊 
				if(root->mem==-1){
					root->mem = mem;
        			mem += 4;
        		}
        		leftmem = root->mem;
        	}
			else{
				if(root->mem==-1){
					for(int i=3; i<mem/4; i++){ //找這個變數之前有沒有用過，有的話是存在哪個mem 
        				if(strcmp(table[i].name, root->lexeme)==0){
        					root->mem = i*4;
							break; 
						}
					}
				}
				if(root->mem==-1){
					printf("EXIT 1");
					exit(0);
				}
				root->reg = reg;
				printf("MOV r%d [%d]\n", reg++, root->mem);
			}
			break; 
        case INT:
        	root->reg = reg;
        	printf("MOV r%d %d\n", reg++, root->val);
            break;
        case ASSIGN:
        case ADDSUB:
        case MULDIV:
            evaluateTree(root->left);
            evaluateTree(root->right);
            if (strcmp(root->lexeme, "+") == 0){
            	root->reg = root->left->reg;
                printf("ADD r%d r%d\n", root->left->reg, root->right->reg);
                reg--;
        	}
            else if (strcmp(root->lexeme, "-") == 0){
            	root->reg = root->left->reg;
            	printf("SUB r%d r%d\n", root->left->reg, root->right->reg);
				reg--;
        	}
            else if (strcmp(root->lexeme, "*") == 0){
            	root->reg = root->left->reg;
				printf("MUL r%d r%d\n", root->left->reg, root->right->reg);
				reg--;
        	}
            else if (strcmp(root->lexeme, "/") == 0){
            	root->reg = root->left->reg;
				printf("DIV r%d r%d\n", root->left->reg, root->right->reg);
				reg--;
        	}
            else if (strcmp(root->lexeme, "=") == 0){
            	root->reg = root->right->reg;
            	printf("MOV [%d] r%d\n", root->left->mem, root->right->reg);
            	reg--;
            	leftmem = -1;
            	flag = -1;
        	}
            else if (strcmp(root->lexeme, "&") == 0){
            	root->reg = root->left->reg;
				printf("AND r%d r%d\n", root->left->reg, root->right->reg);
				reg--;
			}
            else if (strcmp(root->lexeme, "|") == 0){
            	root->reg = root->left->reg;
				printf("OR r%d r%d\n", root->left->reg, root->right->reg);
				reg--;
        	}
            else if (strcmp(root->lexeme, "^") == 0){
            	root->reg = root->left->reg;
				printf("XOR r%d r%d\n", root->left->reg, root->right->reg);
				reg--;
        	}
			break;
        default:
        	printf("EXIT 1");
        	exit(0);
        }
    }
}
