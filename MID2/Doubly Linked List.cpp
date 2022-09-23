#include <iostream>
#include <string>
#include <stdexcept>
//#include "function.h"
using namespace std;

class ListNode{
private:
    int data;
    ListNode *next;
    ListNode *prev;
public:
    ListNode():data(0),next(nullptr), prev(nullptr){};
    ListNode(int a):data(a),next(nullptr), prev(nullptr){};

    friend class List;
};

class List {
private:
    ListNode* head;  // head of the doubly linked list
    ListNode* tail;  // tail of the doubly linked list
    ListNode* middle; // middle of the list
    int       cnt;   // total count of the elements in the list
    int       pos;   // the position of middle

    void reset(){
        head = nullptr;
        tail = nullptr;
        middle = nullptr;
        cnt = 0;
        pos = 0;
    }

    void clean(){
        ListNode* temp;
        while(head!=nullptr){
            temp = head;
            head = head->next;
            delete temp;
        }
    }

public:
    // constructor and destructor
    List(){
        reset();
    }

    ~List(){
        clean();
    }

    void InsertHead(int data);
    int  RemoveHead();
    void InsertTail(int data);
    int  RemoveTail();
    void Swap();
    int  getSize();
    int  getMiddle();

};

void List::InsertHead(int data)
{
	ListNode* temp = new ListNode(data);
	
	cnt++;
	pos = (cnt/2)+1;
	
	if(head==nullptr){
		head = temp;
		tail = temp;
		middle = temp;	
	} 
	else{
		temp->next = head;
		head->prev = temp;
		head = temp;
		if(cnt%2==1){
			middle = middle->prev;
		}
	}
}
 
int List::RemoveHead()
{
	if(head!=nullptr){
		cnt--;
		pos = (cnt/2)+1;
		
		ListNode* temp = head;
		int data = head->data;
		
		if(head==tail){
			head = NULL;
			tail = NULL;
			middle = NULL;
		}
		else{
			head = head->next;
			head->prev = nullptr;
			if(cnt%2==0){
				middle = middle->next;
			}
		}
		delete temp;
		return data;
	}
	else{
		throw std::out_of_range("out of range");
	}
}
 
void List::InsertTail(int data)
{
	ListNode* temp = new ListNode(data);
	
	cnt++;
	pos = (cnt/2)+1;
	
	if(tail==nullptr){
		head = temp;
		tail = temp;
		middle = temp;
	} 
	else{
		tail->next = temp;
		temp->prev = tail;
		tail = temp;
		if(cnt%2==0){
			middle = middle->next;
		}
	}
}
 
int List::RemoveTail()
{
	if(tail!=nullptr){
		cnt--;
		pos = (cnt/2)+1;
		
		ListNode* temp = tail;
		int data = tail->data;
		
		if(tail==head){
			head = NULL;
			tail = NULL;
			middle = NULL;
		}
		else{
			tail = tail->prev;
			tail->next = nullptr;
			if(cnt%2==1){
				middle = middle->prev;
			}
		}
		delete temp;
		return data;
	}
	else{
		throw std::out_of_range("out of range");
	} 
	
}

void List::Swap()
{
	if(head==tail) return;
	
	ListNode* temp1 = head;
	ListNode* temp2 = tail;
	
	head = middle;
	tail = middle->prev;
	tail->next = nullptr;
	head->prev = nullptr;
	temp2->next = temp1;
	temp1->prev = temp2;
	if(cnt%2==1) middle = temp2;
	else middle = temp1;
}
 
int List::getSize()
{
	return cnt;
}

int List::getMiddle()
{
	return pos;
} 

int main(){
    List L;
    string cmd;
    int data, cnt=0, pos = 0;

    while(cin >> cmd){
        if(cmd=="IH"){ // insert an integer to the head
            cin >> data;
            L.InsertHead(data);
        } else if (cmd=="IT"){ // insert an integer to the end
            cin >> data;
            L.InsertTail( data);
        } else if (cmd=="RH"){   // print and remove a node from head
            try {
                cout<< L.RemoveHead() <<endl;
            } catch (const out_of_range &e){
                cout << endl;
            }
        } else if (cmd=="RT") {// print and remove a node from tail
            try {
                cout << L.RemoveTail()<<endl;
            } catch (const out_of_range &e){
                cout << endl;
            }
        } else if (cmd=="S"){
            L.Swap();
        }
    }
}
