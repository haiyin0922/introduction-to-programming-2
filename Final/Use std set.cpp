#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

void printVector(vector<int> v)
{
    for(int i=0;i < v.size();i++){
        cout<<v[i]<<" ";
    }
    cout<<endl;
}

vector<int> readVector()
{
    int i=0;
    vector<int> new_vector;

    while(cin>>i){
        if(i==0) break;

        new_vector.push_back(i);
    }
    
	return new_vector;
}

int getValue(vector<int> v)
{
    int value = 0;
    int size = v.size();
    
	for(int i=0; i<size; i++){
        value += (size-i) * v[i];	//v.at(i) �s�����ޭȬ�i���� 
    }
    
	return value;
}

struct mycompare
{
    bool operator() (const vector<int>& lhs, const vector<int>& rhs) const{
        return getValue(lhs) < getValue(rhs);	//��set�����ƦC����value�ɧǱƦC 
    }
};

main()
{
    set<vector<int>, mycompare> s;
    string command;

    while(cin>>command){
        if(command == "insert"){
            vector<int> t = readVector();	//Ū�i�@�ӼƦCt
            for(auto it: s){
            	if(getValue(t) == getValue(it)){	//t��value�p�G�w�g�bset���X�{�L 
            		cout<<"exist"<<endl;
            		s.erase(it);
            		reverse(t.begin(),t.end());
            		break;
            	}
            }
            s.insert(t);	//t��value�S�X�{�L�N����insert�iset�A�����ܥ�reverse 
        }
        else if(command == "range_out"){
            int from=getValue(readVector());
            int to=getValue(readVector());
            for(auto it: s){
                if((getValue(it) >= from) && (getValue(it) <= to)){
                    printVector(it);
                }
                else if(getValue(it) > to) break;
            }
        }
        else if(command == "output"){
            for(auto it: s){
                printVector(it);
            }
        }
    }
}
