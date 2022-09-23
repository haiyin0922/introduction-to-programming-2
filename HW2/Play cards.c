#include<stdio.h>
#include<string.h>
#include <stdlib.h>

typedef struct _Node{
    int number;
    struct _Node* next;
}Node;

Node* head;
Node* createList(int n);
void printandfree();
void ADD(int idx, int num);
void CUT(int a, int b);
int value[20000] = {0};

int main()
{
	int n, m, i;
	int idx, num, a, b;
	char operation[4], add[4] = "ADD", cut[4] = "CUT";
	
	scanf("%d%d", &n, &m);
	
	for(i=0; i<n; i++){
		scanf("%d", &value[i]);
	}

	head = createList(n);

	for(i=0; i<m; i++){
		scanf("%s", operation);
	
		if(strcmp(operation, add)==0){
			scanf("%d%d", &idx, &num);
			ADD(idx, num);
		} 
		if(strcmp(operation, cut)==0){
			scanf("%d%d", &a, &b);
			CUT(a, b);
		}
	}	
	
	printandfree();
	
	return 0;
}

void ADD(int idx, int num)
{
	Node* temp, *card;
	int i;
	
	card = (Node*)malloc(sizeof(Node));
	card->number = num;
	
	if(idx==0){
		card->next = head;
		head = card;
	}
	
	if(idx>0){
		temp = head;
		for(i=0; i<idx-1; i++){
			temp = temp->next;
		}
		card->next = temp->next;
		temp->next = card;
	} 
}

void CUT(int a, int b)
{
	Node* P, *Q, *temp;
	int i;
	
	if(a>0){
		temp = head;
		for(i=0; i<a-1; i++){
			temp = temp->next;
		}
		P = temp;
		temp = temp->next;
		Q = temp;
	
		temp = head;
		for(i=0; i<a+b-1; i++){
			temp = temp->next;	
		}
		P->next = temp->next;
		temp->next = head;
		head = Q;
	}
}

Node* createList(int n)
{
	int i;
	Node* temp;
	
	head = (Node*)malloc(sizeof(Node));
	temp = head;
	
    for(i=0; i<n-1; i++){
        temp->number = value[i];
        temp->next = (Node*)malloc(sizeof(Node));
        temp = temp->next;
    }
    temp->number = value[i];
    temp->next = NULL;
    
    return head;
}

void printandfree()
{
	Node* temp1, *temp2;
	
	temp1 = head;
    while(temp1!=NULL) {
        printf("%d\n", temp1->number);
        temp2 = temp1;
        temp1 = temp1->next;
        free(temp2);
    }
}
