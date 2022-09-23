#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
    int data;
    struct _Node *next;
} Node;

void rotateList(Node**,int);
void freeList(Node *head);
Node* createList();
void printList(Node *head);

int main() {
	Node *head = NULL;
	Node *temp;
	int data;
	int k;

    head = createList();
	scanf("%d",&k);	
	rotateList(&head,k);
	printList(head);
	freeList(head);
	return 0;
}

void freeList(Node *head)
{
	Node *temp;
	for(temp=head; temp!=NULL; temp=head)
	{
		head = head->next;
		free(temp);
	}
}

Node* createList(){
    Node* head = NULL;
    Node* temp = NULL;
    int data;

    while(1){
        scanf("%d",&data);
        if(data>-1){
            if (temp==NULL) {
                temp = (Node*) malloc(sizeof(Node));
                head = temp;
            } else {
                temp->next = (Node*) malloc(sizeof(Node));
                temp = temp->next;
            }
            temp->data = data;
            temp->next = NULL;
        } else break;
    }
    return head;
}

void printList(Node *head)
{
	Node *temp=head;
	printf("%d", temp->data);
	temp=temp->next;
	
	for(; temp!=NULL; temp=temp->next)
	{
		printf(" %d", temp->data);
	}
	printf("\n");
}

void rotateList(Node** head,int new_head)
{
	Node* temp;
	int i;
	
	temp = *head;
	while(temp->next!=NULL){
		temp = temp->next;
	}
	temp->next = *head;
	
	temp = *head;
	for(i=0; i<new_head-1; i++){
		temp = temp->next;
	}
	*head = temp->next;
	temp->next = NULL;
} 
