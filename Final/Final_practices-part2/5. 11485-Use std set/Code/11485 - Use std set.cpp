#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

void printVector(vector<int> v)
{
    for(int i=0;i < v.size();i++)
    {
        cout<<v.at(i)<<" ";
    }
    cout<<'\n';
}
vector<int> readVector()
{
    int i=0;
    vector<int> new_vector;

    while(cin>>i)
    {
        if(i==0) break;

        new_vector.push_back(i);
    }
    return new_vector;
}
int getValue(vector<int> v)
{
    int value = 0;
    int size = v.size();
    for(int i=0; i<size; i++)
    {
        value += (size-i) * v.at(i); 
    }
    return value;
}

struct mycompare
{
    bool operator() (const vector<int>& lhs, const vector<int>& rhs) const
    {
        return getValue(lhs) < getValue(rhs); 
    }
};

int main()
{
    set<vector<int>, mycompare> s;
    string command;

    while(cin>>command)
    {
        if(command == "insert")
        {
            vector<int> t = readVector(); 

            set<vector<int>, mycompare>::iterator it;
            for(it=s.begin();it!=s.end();it++)
            {
            	vector<int> cur = *it;
            	if(getValue(t) == getValue(cur))  
            	{
            		cout<<"exist"<<endl;
            		s.erase(cur);
            		reverse(t.begin(),t.end());
            		break;
            	}
            }

            s.insert(t); 
        }
        else if(command == "range_out")
        {
            int from=getValue(readVector());
            int to=getValue(readVector());

            set<vector<int>, mycompare>::iterator it;
            for(it=s.begin();it!=s.end();it++)
            {
                vector<int> cur = *it;
                int keyvalue=getValue(cur);
                if((keyvalue >= from) && (keyvalue <= to))
                {
                    printVector(cur);
                }
                else if(keyvalue > to) break;
            }
        }
        else if(command == "output")
        {
            set<vector<int>, mycompare>::iterator it;
            for(it=s.begin();it!=s.end();it++)
            {
                vector<int> cur = *it;
                printVector(cur);
            }
        }
    }
    return 0;
}
