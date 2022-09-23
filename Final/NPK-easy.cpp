#include <iostream>
#include <queue>
#include <string>
#include <list>
#include <algorithm>

using namespace std;
list<int> line;	//��a���� 
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
            country[num].push(id);	//��o�ӤH��id push��L��a��queue 
            if(find(line.begin(),line.end(),num)==line.end()) line.push_back(num);	//�p�G�o�Ӱ�a�S�X�{�L�Apush��line��back 
        }
        else if(s=="DEQUEUE"){
            int num = line.front();
            cout << country[num].front() << endl;	//�Ĥ@�Ӱ�a���Ĥ@�ӤH 
            country[num].pop();
            if(country[num].empty()) line.pop_front();	//�S�H�F�Npop�հ�a 
        }
    }
    return 0;
}
