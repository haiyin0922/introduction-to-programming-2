#include <stdio.h>
#include <stdlib.h>
//#include "function.h"

typedef struct treeNode
{
    int data;
    struct treeNode *left;
    struct treeNode *right;
} Node;

Node* buildTree(int* inorder, int* preorder, int inorder_start, int inorder_end);
void caculateLeafNodesSum(Node* root);
void freeTree(Node *root);

void freeTree(Node *root)
{
    if(root != NULL)
    {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main(void){

    int i,n;
    int *inorder,*preorder;
    scanf("%d",&n); // n : the size of binary tree
    /*------------Parse the input----------------*/
    inorder = (int *) malloc(n * sizeof(int));
    preorder = (int *) malloc(n * sizeof(int));
    for(i=0; i<n; i++) scanf("%d", &inorder[i]);
    for(i=0; i<n; i++) scanf("%d", &preorder[i]);
    /*------------Build the binary tree----------*/
    Node *root = buildTree(inorder, preorder, 0, n-1);
    /*------------Print out the tree ------------*/
    caculateLeafNodesSum(root);
    freeTree(root);
    free(inorder);
    free(preorder);
    return 0;
}

Node *buildTree(int* inorder, int *preorder, int inorder_start, int inorder_end)
{
	int i;
	static pos = 0;
	
	Node *root = (Node*)malloc(sizeof(Node));
	root->data = *(preorder+pos);
	root->left = NULL;
    root->right = NULL;

	for(i=inorder_start; i<=inorder_end; i++){
		if(*(inorder+i)==*(preorder+pos))
			break;
	}
	
	if(i!=inorder_start){
		pos++;
		root->left = buildTree(inorder, preorder, inorder_start, i-1);
	}
	
	if(inorder_end-i>0){
		pos++;
		root->right = buildTree(inorder, preorder, i+1, inorder_end);
	}
	
	return root;
}

void caculateLeafNodesSum(Node* root)
{
	static sum = 0;
	static flag = 0;
	static rootdata = 0;
	
	if(flag==0){
		rootdata = root->data;
		flag++;
	}
	
	if(root->left!=NULL){
		caculateLeafNodesSum(root->left);
	}	
	
	if(root->right!=NULL){ 
		caculateLeafNodesSum(root->right);
	}
	
	if(root->left==NULL && root->right==NULL){
		sum += root->data;
	}
	
	if(root->data==rootdata){
		printf("%d\n", sum);
	}
	
	return;
} 
