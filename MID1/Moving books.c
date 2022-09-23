#include<stdio.h>
#include<string.h>
#include <stdlib.h>

typedef struct _Node{
	int number;
	int table;
    struct _Node* next;
    struct _Node* prev;
}Node;

Node* book[25];
Node* table[25];
void creatList();
void moveonto();
void moveover();
void pileonto();
void pileover();
void goback();
int n;

int main()
{
	int i, a, b;
	char operation1[5], operation2[5]; 
	char exit[5] = "exit", move[5] = "move", pile[5] = "pile", onto[5] = "onto", over[5] = "over";
	Node* temp, *P;
	
	scanf("%d", &n);	
	creatList(n);
	
	scanf("%s", operation1);
	while(strcmp(operation1, exit)!=0){
		scanf("%d%s%d", &a, operation2, &b);
		if(strcmp(operation1, move)==0 && strcmp(operation2, onto)==0 && book[a]->table!=book[b]->table)
			moveonto(a, b);
		else if(strcmp(operation1, move)==0 && strcmp(operation2, over)==0 && book[a]->table!=book[b]->table)
			moveover(a, b);
		else if(strcmp(operation1, pile)==0 && strcmp(operation2, onto)==0 && book[a]->table!=book[b]->table)
			pileonto(a, b);
		else if(strcmp(operation1, pile)==0 && strcmp(operation2, over)==0 && book[a]->table!=book[b]->table)
			pileover(a, b);
		scanf("%s", operation1);
	} 
	
	for(i=0; i<n; i++){
		printf("%d:", i);
		temp = table[i]->next;
		while(temp!=NULL){
			printf(" %d", temp->number);
			P = temp;
			temp = temp->next;
			free(P);
		}
		printf("\n");
	}
	
	return 0;
}

void creatList(int n)
{
	int i;
	
    for(i=0; i<n; i++){
    	table[i] = (Node*)malloc(sizeof(Node));
    	book[i] = (Node*)malloc(sizeof(Node));
        table[i]->next = book[i];
        table[i]->prev = NULL;
        book[i]->number = i;
        book[i]->table = i;
        book[i]->next = NULL;
        book[i]->prev = table[i];
    }
}

void moveonto(int a, int b)
{
	Node* temp;
	
	goback(book[a]);
	goback(book[b]);
	
	book[b]->next = book[a];
	book[a]->prev->next = NULL;
	book[a]->prev = book[b];
	book[a]->table = book[b]->table;
}

void moveover(int a, int b)
{
	Node* temp;
	
	goback(book[a]);
	
	temp = book[b];
	while(temp->next!=NULL){
		temp = temp->next;
	}
	
	temp->next = book[a];
	book[a]->prev->next = NULL;
	book[a]->prev = temp;
	book[a]->table = book[b]->table;
	
	return; 
}

void pileonto(int a, int b)
{
	Node* temp;
	
	goback(book[b]);
	
	book[b]->next = book[a];
	book[a]->prev->next = NULL;
	book[a]->prev = book[b];
	
	temp = book[a];
	while(temp!=NULL){
		temp->table = book[b]->table;
		temp = temp->next;
	}
}

void pileover(int a, int b)
{
	Node* temp;
	
	temp = book[b];
	while(temp->next!=NULL){
		temp = temp->next;
	}
	
	temp->next = book[a];
	book[a]->prev->next = NULL;
	book[a]->prev = temp;
	
	temp = book[a];
	while(temp!=NULL){
		temp->table = book[b]->table;
		temp = temp->next;
	}
}

void goback(Node* temp)
{
	Node* P;
	
	while(temp->next!=NULL){
		table[temp->next->number]->next = temp->next;
		temp->next->prev = table[temp->next->number];
		temp->next->table = temp->next->number;
		P = temp->next;
		temp->next = NULL;
		temp = P; 
	}
} 
