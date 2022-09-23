#include <iostream>
#include <string.h>
#include <math.h>
//#include "function.h"
using namespace std;

class BST{
public:
    BST():Height(0){}
    virtual ~BST() {}
    virtual void insert(const int &) = 0;
    virtual bool search(const int &) const = 0;
    virtual void print() const = 0;
    int height() const { return Height; }// An empty tree has height of 0. A tree with only root node has height of 1.

protected:
    int Height;
};

class Array_BST : public BST{
public:
    Array_BST();
    virtual ~Array_BST() {}
    virtual void insert(const int &) override; //root node is stored at index 1.
    virtual bool search(const int &) const override;
    virtual void print() const override{
        int k = pow(2, height());
        for (int i = 1; i <= k-1; i++) {
            if (array[i] != 0)
                cout << array[i] << " ";
        }
    }

private:
    int array[1025];
};

class ListNode{
    friend class List_BST; //make List_BST a friend

public:
    ListNode(const int &info):key( info ),left( NULL ),right( NULL ) //constructor
    {
    }//end ListNode constructor

private:
    int key;
    ListNode *left;
    ListNode *right;
};//end class ListNode

class List_BST : public BST{
public:
    List_BST();
    virtual ~List_BST()
    {
        deleteTree(root);
    }
    virtual void insert(const int &) override;
    virtual bool search(const int &) const override;
    virtual void print() const override{
        int i;
        for(i = 1; i <= Height; i++){
            printGivenLevel(root, i);
        }
    }

private:
    ListNode *root;
    // private member functions
    ListNode* createLeaf(int key) const; //new a ListNode and return its address
    /* clean a tree.*/
    void deleteTree(ListNode *root);

    void printGivenLevel(ListNode* Ptr, int level) const {
        if (Ptr == NULL)
            return;
        if (level == 1)
            cout << Ptr->key << " ";
        else if (level > 1)
        {
            printGivenLevel(Ptr->left, level-1);
            printGivenLevel(Ptr->right, level-1);
        }
    }
};

void BSTManipulator(BST& bstobj1,BST& bstobj2, char cmd ){
    int n;
    if (cmd == 'I') {
        cin >> n;
        bstobj1.insert(n);
        bstobj2.insert(n);
    }else if (cmd == 'S'){
        cin >> n;
        if (bstobj1.search(n)) {
            cout << "yes" << endl;
        }else{
            cout << "no" << endl;
        }

        if (bstobj2.search(n)) {
            cout << "yes" << endl;
        }else{
            cout << "no" << endl;
        }

    }else if (cmd == 'H'){
        cout << bstobj1.height() << endl;;
        cout << bstobj2.height() << endl;;

    }else if (cmd == 'P'){
        bstobj1.print();
        cout << endl;
        bstobj2.print();
        cout << endl;
    }
}

Array_BST::Array_BST()
{
	for(int i=1; i<1025; i++){
		array[i] = 0;
	}
	
	Height = 0;
}

void Array_BST::insert(const int &a)	//root node is stored at index 1.
{
	int i = 1;
	int layer = 1;
	
	if(array[1]==0){
		array[1] = a;
	}
	else{
		while(1){
			if(a==array[i]) return;
			layer++;
			if(a>array[i]){
				if(array[2*i+1]==0){
					array[2*i+1] = a;
					break;
				}
				else i = 2*i+1;
			}
			else{
				if(array[2*i]==0){
					array[2*i] = a;
					break;
				}
				else i = 2*i;
			}
		}
	}
	
	if(layer>Height) Height = layer;
}

bool Array_BST::search(const int &a) const
{
	int i=1;
	
	while(array[i]!=0){
		if(array[i]==a) return true;
		else{
			if(a>array[i]) i=2*i+1;
			else i = 2*i;
		}
	}
	
	return false;
}
    
List_BST::List_BST()
{
	root = NULL;
	
	Height = 0;
}

void List_BST::insert(const int &a)
{	
	int layer = 1;
	
	if(root==NULL){
		root = createLeaf(a);
	}
	else{
		ListNode* temp = root;
		while(1){
			if(a==temp->key) return;
			layer++;
			if(a>temp->key){
				if(temp->right==NULL){
					temp->right = createLeaf(a);
					break;	
				}
				else temp = temp->right; 
			}
			else{
				if(temp->left==NULL){
					temp->left = createLeaf(a);
					break;
				}
				else temp = temp->left;
			}
		}
	}
	
	if(layer>Height) Height = layer;

}	

bool List_BST::search(const int &a) const
{
	ListNode* temp = root;
	
	while(temp!=NULL){
		if(a==temp->key) return true;
		else if(a>temp->key){
			temp = temp->right;
		}
		else{
			temp = temp->left;
		}
	}
	
	return false;
}

ListNode* List_BST::createLeaf(int key) const	//new a ListNode and return its address
{
	ListNode* node = new ListNode(key);
	
	return node;
}

void List_BST::deleteTree(ListNode *root)
{
	if(root!=NULL){
    	deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }
}

int main(){
    Array_BST A_bst;
    List_BST B_bst;
    char cmd;

    while (cin >> cmd)
        BSTManipulator(A_bst, B_bst, cmd);

    return 0;
}
