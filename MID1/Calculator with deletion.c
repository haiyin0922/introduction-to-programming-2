#include<stdio.h>
#include<stdlib.h>

typedef struct _node {
    char data;
    struct _node *left;
    struct _node *right;
    struct _node* parent;
} Node;

Node *pre_parser(char expr[]);
Node *makeNode(int pos, char expr);
int evalBoolExpr(Node *root);
Node *deletion(Node* root, int from, int to);
Node *position[300000];
	
int main()
{
	int i=0, j=0, N;
	Node *root, *cur;
	char expr[300000];
	int delete_from, delete_to;
	
	scanf("%d ", &N);
	
	while(i==0 || expr[i-1]!='\n'){
		scanf("%c", &expr[i++]);
	}
	
	root = pre_parser(expr);
	printf("%d\n", evalBoolExpr(root)%10007);
	
	for(j=0; j<N; j++){
		scanf("%d%d", &delete_from, &delete_to);
		root = deletion(root, delete_from, delete_to);
		printf("%d\n", evalBoolExpr(root)%10007);
	}

	for(j=1; j<i; j++){
		free(position[j]);
	}
	
	return 0;
}

Node *makeNode(int pos, char expr)
{
    position[pos] = (Node*)malloc(sizeof(Node));
	position[pos]->data = expr;
	position[pos]->left = NULL;
    position[pos]->right = NULL;
    position[pos]->parent = NULL;
    
    return position[pos];
}

Node* pre_parser(char expr[])
{
	Node *node;
   	static pos = 0; // a static variable to remember the current position in the expr[]
	
    if(expr[pos]>='1' && expr[pos]<='9') // prefix = ID
        return makeNode(pos, expr[pos++]);
   	else if(expr[pos]=='+' || expr[pos]=='-' || expr[pos]=='*'){ // prefix = OP <prefix> <prefix>
    	node = makeNode(pos, expr[pos++]);
      	node->left = pre_parser(expr);
      	node->left->parent = node;
     	node->right = pre_parser(expr);
     	node->right->parent = node;

      	return node;
   	}
}

int evalBoolExpr(Node *root)
{
	int op1, op2;
	
	if(root->data=='+' || root->data=='-' || root->data=='*'){
   		op1 = evalBoolExpr(root->left);
   		op2 = evalBoolExpr(root->right);
   		if(root->data=='+')
			return (op1+op2)%10007;
		else if(root->data=='-')
			return (op1-op2)%10007;
		else if(root->data=='*')
			return (op1*op2)%10007;
   	}
	else
		return (root->data)-'0';
}

Node* deletion(Node* root, int from, int to)
{	
	
	Node* temp;
	int i;
	
	if(position[from]==root){
		root = position[to+1];
	}
	else if(position[from]==position[from]->parent->left){
		position[from]->parent->left = position[to+1];
		position[to+1]->parent = position[from]->parent;
	}
	else{
		position[from]->parent->right = position[to+1];
		position[to+1]->parent = position[from]->parent;
	}
	
	for(i=0; position[to+1+i]!=NULL; i++){
		position[from+i] = position[to+1+i];
	}	

	return root;
}
