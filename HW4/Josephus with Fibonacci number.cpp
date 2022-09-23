#include <iostream>
//#include "function.h"
using namespace std;

class Node
{
   	friend class Josephus;
   	public:
        Node():next( NULL ){
        }
        Node( const int &info ) //constructor
      	:number( info ), next( NULL )
    	{
    	} //end ListNode constructor
    	
   	private:
    	Node *next;
        int number;
};//end class Node

class Josephus
{
	public:
        Josephus();
        ~Josephus();
        Josephus(const int &);
        int kill(); // return the survival¡¦s position
        
    private:
        void generatecircularlinkedList(const int &); // generate circular linked-list
        void generateFib(const int &); // generate a Fibonacci sequence table
        int sequence[50]; // store Fibonacci number
        int noOfPeople;
        Node *head;
};

int main(){
	int numofpeople;

	while(cin>>numofpeople){
		Josephus Jose(numofpeople);
		int survival = Jose.kill();
		cout<<survival<<endl;
    }
}

Josephus::Josephus()
{
	head = new Node(1);
	head->next = NULL;
	noOfPeople = 1; 
}

Josephus::~Josephus()
{
	delete head;
}

Josephus::Josephus(const int &num)
{
	head = new Node(num);
	head->next = NULL;
	noOfPeople = num;
	
	generatecircularlinkedList(num);
	generateFib(num);
}

int Josephus::kill()// return the survival¡¦s position
{
	Node* temp = head;
	
	if(temp->next!=NULL){
		Node* temp2;
		int num = 0;
		int i;
	
		while(num<noOfPeople-1){
			i = sequence[num]%(noOfPeople-num);
			if(i==0){
				temp2 = temp;
				for(temp=temp->next; temp->next!=temp2; temp=temp->next){
				}
			}
			else{
				while(i>1){
					temp = temp->next;
					i--;
				}
				temp2 = temp->next;
			}
			temp->next = temp2->next;
			delete temp2;
			num++;
		}
	}
	
	head = temp;
	return head->number; 
}

void Josephus::generatecircularlinkedList(const int &num) // generate circular linked-list
{
	Node* temp = head;
	
	for(int i=1; i<num; i++){
        temp->next = new Node(i);
        temp = temp->next;
    }
    temp->next = head;
}

void Josephus::generateFib(const int &num) // generate a Fibonacci sequence table
{
	sequence[0] = 1;
	sequence[1] = 1;
	
	for(int i=2; i<num-1; i++){
		sequence[i] = sequence[i-1] + sequence[i-2]; 
	}
}
