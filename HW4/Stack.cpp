#include<iostream>
#include<string.h>
//#include "function.h"
using namespace std;

class ListNode
{
    friend class List_stack; //make List_stack a friend
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

class List_stack {
    public:
        List_stack();
        ~List_stack();
        void push(const int &);
        void pop();
        void print();
    private:
        ListNode *head;
        ListNode *tail;
};

int main(){
    List_stack L_stack;
    char command[10];
    int n;
    while(cin>>command){

        if(strcmp(command,"pop")==0){
            L_stack.pop();
        }else if(strcmp(command,"push")==0){
            cin >> n;
            L_stack.push(n);
        }else if(strcmp(command, "print") == 0){
            L_stack.print();
            cout << endl;
        }
    }
    return 0;
}

List_stack::List_stack()
{
	head = NULL;
	tail = NULL;
}
 
List_stack::~List_stack()
{
	ListNode* temp, *temp2;
	
	for(temp=head; temp->nextPtr!=NULL; ){
		temp2 = temp;
		temp = temp->nextPtr;
		delete temp2;
	}
	delete temp;
}
 
void List_stack::push(const int &n)
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
 
void List_stack::pop()
{
	ListNode* temp;
	
	if(head==NULL) return;
	else if(head==tail){
		head = NULL;
		tail = NULL;
	}
	else{ 
		temp = tail;
		tail = tail->prevPtr;
		tail->nextPtr = NULL;
		delete temp;
	}
}
 
void List_stack::print()
{
	ListNode* temp;
	
	if(head==NULL) return;
	else{
		for(temp=tail; temp!=head; temp=temp->prevPtr){
			cout<<temp->data<<" ";
		}
		cout<<temp->data;
	}
}
