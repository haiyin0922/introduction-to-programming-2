#include <stdlib.h>
#include <stdio.h>
typedef struct _node {
    int value;
    struct _node *left;
    struct _node *right;
} Node;

Node *create_node(int value);
void postorder(Node *root);
Node *build(int *preorder, int inorder_start, int inorder_end);
int in_index[200000], pre_to_in_index[200000];

int main()
{ 
	int i, n;
	Node *root;
	int in[200000], pre[200000];
	
	scanf("%d", &n);
	
	for(i=0; i<n; i++){
		scanf("%d", &in[i]);
		in_index[in[i]] = i;
	}	
	for(i=0; i<n; i++){
		scanf("%d", &pre[i]);
		pre_to_in_index[i] = in_index[pre[i]];
	}
	
	postorder(build(pre, 0, n));
	printf("\n");
	
	return 0;	
}

Node *create_node(int value)
{
    Node *root = (Node*)malloc(sizeof(Node));
	root->value = value;
	root->left = NULL;
    root->right = NULL;
    
    return root;
}

void postorder(Node *root)
{		
	if(root->left!=NULL){
		postorder(root->left);
	}
	if(root->right!=NULL){
		postorder(root->right);
	}
	printf("%d ", root->value); 
	free(root);
	
	return;
}

/*
    Parameter description:
    int *preorder : the preorder traversal sequence of the binary tree.
    int inorder_start : the starting index of the inorder traversal of the subtree.
    int inroder_end : the ending index of the inorder traversal of the subtree.

    As for the preorder traversal index, try declaring a static variable inside this function.
*/
Node *build(int *preorder, int inorder_start, int inorder_end)
{
	int pos = 0;
	static i = 0;
	Node *root;
	
	root = create_node(*(preorder+i));
	
	pos = pre_to_in_index[i];
	
	if(pos!=inorder_start){
		i++;
		root->left = build(preorder, inorder_start, pos);
	}
	if(inorder_end-pos>1){
		i++;
		root->right = build(preorder, pos+1, inorder_end);
	}
	
	return root;
}
