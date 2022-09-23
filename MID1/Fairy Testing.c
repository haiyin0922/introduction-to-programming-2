#include<stdio.h>
#include<stdlib.h> 

typedef enum {ID, AND, OR} TokenSet;

typedef struct node{
    int value; // This is the value of the subtree, not the ID number
    int tokentype;
    struct node *left;
    struct node *right;
    struct node *parent; //pointing to the parent node
}Node;

Node* variable[100001];

Node* makeNode();
void freeTree(Node *root);
Node* pre_parser(char expr[]);

int pos = 0;

int main()
{
	int T, N, M, flip;
	char expr[1000000];
	int i, j;
	Node* root, *cur, *pa;
	
	scanf("%d", &T);
	
	for(i=0; i<T; i++){
		scanf("%d%d%s", &N, &M, expr);
		pos = 0;
		root = pre_parser(expr);
		for(j=0; j<M; j++){
			scanf("%d", &flip);
			cur = variable[flip];
			cur->value ^= 1;
			while(cur!=root){
				pa = cur->parent;
				if(pa->tokentype==1)
					pa->value = pa->left->value & pa->right->value; 
				else if(pa->tokentype==2)
					pa->value = pa->left->value | pa->right->value;
				cur = pa;
			}
			printf("%d\n", root->value);
		}
		freeTree(root);
	}
		
	return 0;
}

Node* makeNode()
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->value = 0;
	node->left = NULL;
	node->right = NULL;
	node->parent = NULL; 
	
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
	int sum = 0;
	
	if(expr[pos]=='&' || expr[pos]=='|'){ // prefix = OP <prefix> <prefix>
    	node = makeNode();
    	if(expr[pos]=='&')
			node->tokentype = 1;
		if(expr[pos]=='|')
			node->tokentype = 2;
    	pos++;
      	node->left = pre_parser(expr);
      	node->left->parent = node;
     	node->right = pre_parser(expr);
     	node->right->parent = node;

      	return node;
   	}
	
	pos++;
    while(expr[pos]>='0' && expr[pos]<='9'){ // prefix = ID
    	sum = sum*10+expr[pos]-'0';
		pos++;
	}
	pos++;
	variable[sum] = makeNode();
	variable[sum]->tokentype = 0;
	
	return variable[sum];
}
