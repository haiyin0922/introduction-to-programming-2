#include <stdio.h>
#include <stdlib.h>

typedef struct _Node{
    int number;
    struct _Node* next;
    struct _Node* prev;
}Node;

Node* head;
Node* createList(int n);
void freeList();
int solveJosephus(int step);

int main(){

    int n, m;

    while(scanf("%d%d", &n, &m)!=EOF){
        head = createList(n);
        printf("%d\n", solveJosephus(m));
        freeList();
    }

    return 0;
}

Node* createList(int n)
{
	int i;
	Node* temp;
	
	head = (Node*)malloc(sizeof(Node));
	temp = head;
	
    for(i=1; i<n; i++){
        temp->number = i;
        temp->next = (Node*)malloc(sizeof(Node));
        temp->next->prev = temp;
        temp = temp->next;
    }
    temp->number = i;
    temp->next = head;
    temp->next->prev = temp;
    
    return head;
}
 
void freeList()
{
    free(head);
}
 
int solveJosephus(int step)
{
	int i, j = 0;
	int n = head->prev->number;
	Node* temp, *P;
	
	temp = head;
		
	while(j<n){
		j++;
		if(j<n){
			for(i=1; i<step; i++){
				temp = temp->next;	
			}
			P = temp;
			temp = P->prev;
			temp->next = P->next;
			temp->next->prev = temp;
			free(P);
		}
		
		j++;
		if(j<n){
			for(i=1; i<step; i++){
				temp = temp->prev;	
			}
			P = temp;
			temp = P->next;
			temp->prev = P->prev;
			temp->prev->next = temp;
			free(P);
		}
	}
	
	head = temp;
	
	return head->number;
}
