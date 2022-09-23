#include <iostream>
#include <queue>
#include <string>
#include <list>
#include <algorithm>

using namespace std;
list<int> line;	//國家順序 
queue<int> country[3];

int main()
{
    string s;
    int n, id;

    cin >> n;
    for(int i=0; i<n; i++){
        cin >> s;
        if(s=="ENQUEUE"){
            cin >> id;
            int num = id%3;
            country[num].push(id);	//把這個人的id push到他國家的queue 
            if(find(line.begin(),line.end(),num)==line.end()) line.push_back(num);	//如果這個國家沒出現過，push到line的back 
        }
        else if(s=="DEQUEUE"){
            int num = line.front();
            cout << country[num].front() << endl;	//第一個國家的第一個人 
            country[num].pop();
            if(country[num].empty()) line.pop_front();	//沒人了就pop調國家 
        }
    }
    return 0;
}
