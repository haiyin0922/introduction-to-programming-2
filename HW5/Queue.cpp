#include<iostream>
#include<string.h>
//#include "function.h"
using namespace std;

class ListNode
{
    friend class List_queue; //make List_queue a friend
    public:
        ListNode( const int &info ) //constructor
        : data( info ), nextPtr( NULL ), prevPtr( NULL )
        {
        } //end ListNode constructor
    private:
        int data; //data
        ListNode *nextPtr; // next node in list
        ListNode *prevPtr;
}; //end class ListNode

class List_queue {
    public:
        List_queue();
        ~List_queue();
        void enqueue(const int &);
        void dequeue();
        void print();
    private:
        ListNode *head;
        ListNode *tail;
};

int main(){
    List_queue L_queue;
    char command[10];
    int n;
    while(cin>>command){

        if(strcmp(command,"dequeue")==0){
            L_queue.dequeue();
        }else if(strcmp(command,"enqueue")==0){
            cin >> n;
            L_queue.enqueue(n);
        }else if(strcmp(command, "print") == 0){
            L_queue.print();
            cout << endl;
        }
    }
    return 0;
}

List_queue::List_queue()
{
	head = NULL;
	tail = NULL;
} 

List_queue::~List_queue()
{
	ListNode* temp, *temp2;
	
	for(temp=head; temp!=tail; ){
		temp2 = temp;
		temp = temp->nextPtr;
		delete temp2;
	}
	delete temp; 
}
 
void List_queue::enqueue(const int &n)
{
	ListNode* temp = new ListNode(n);
	
	if(head==NULL){
		head = temp;
		tail = temp;
	}
	else{
		tail->nextPtr = temp;
		temp->prevPtr = tail;
		tail = temp;
	}
}
 
void List_queue::dequeue()
{
	ListNode* temp;
	
	if(head==NULL) return;
	else if(head==tail){
		head = NULL;
		tail = NULL;
	}
	else{
		temp = head;
		head = head->nextPtr;
		head->prevPtr = NULL;
		delete temp;
	}
}
 
void List_queue::print()
{
	ListNode* temp;
	
	if(head==NULL) return;
	else{
		for(temp=head; temp!=tail; temp=temp->nextPtr){
			cout<<temp->data<<" ";
		}
		cout<<tail->data;
	}
}
