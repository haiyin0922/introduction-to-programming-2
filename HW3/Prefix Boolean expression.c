#include<stdio.h>
#include<stdlib.h>

typedef struct _node {
    char data;
    struct _node *left;
    struct _node *right;
} Node;

Node *pre_parser(char expr[]);
Node *makeNode(char expr);
void freeTree(Node *root);
int evalBoolExpr(Node *root, int a, int b, int c, int d);
int abcd[4] = {0};
	
int main()
{
	int i = 0;
	Node *root;
	char expr[30];
	
	while(expr[i-1]!='\n'){
		scanf("%c", &expr[i++]);
	}
	
	root = pre_parser(expr);
		
	for(i=0; i<16; i++){
		abcd[3] = i/8;
		abcd[2] = (i%8)/4;
		abcd[1] = (i%8%4)/2;
		abcd[0] = i%8%4%2;
		printf("%d %d %d %d %d\n", abcd[3], abcd[2], abcd[1], abcd[0], evalBoolExpr(root, abcd[3], abcd[2], abcd[1], abcd[0]));
	}
	
	freeTree(root);
	
	return 0;
}

Node *makeNode(char expr)
{
    Node *node = (Node*)malloc(sizeof(Node));
	node->data = expr;
	node->left = NULL;
    node->right = NULL;
    
    return node;
}

void freeTree(Node *root)
{
    if (root!=NULL)
    {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

Node* pre_parser(char expr[])
{
	Node *node;
   	static pos = 0; // a static variable to remember the current position in the expr[]
	
    if(expr[pos]>='A' && expr[pos]<='D') // prefix = ID
        return makeNode(expr[pos++]);
   	else if(expr[pos]=='&' || expr[pos]=='|'){ // prefix = OP <prefix> <prefix>
    	node = makeNode(expr[pos++]);
      	node->left = pre_parser(expr);
     	node->right = pre_parser(expr);

      	return node;
   	}
}

int evalBoolExpr(Node *root, int a, int b, int c, int d)
{
	int op1, op2;
	
	if(root->data=='&' || root->data=='|'){
   		op1 = evalBoolExpr(root->left, a, b, c, d);
   		op2 = evalBoolExpr(root->right, a, b, c ,d);
   		if(root->data=='&')
			return (op1&op2);
		else if(root->data=='|')
			return (op1|op2);
   	}
	else{
		if(root->data=='A')
			return a;
		else if(root->data=='B')
			return b;
		else if(root->data=='C')
			return c;
		else if(root->data=='D')
			return d;
	}
}
