#include<iostream>
#include<set>
using namespace std;

main()
{
	int n, a, b, root;
	
	set<int> parents;
	set<int> all;

	while(cin>>n){
		if(!n) break;
		else{
			parents.clear();	//�R��set�����Ҧ����� 
			all.clear();
			
			for(int i=0; i<n; i++){
				cin>>a>>b;
				
				parents.insert(a);	//insert���|���ƴ��J�ۦP�ƭȪ�����
				all.insert(a);
				all.insert(b);
			}
			
			cin>>root;
			
			cout<<all.size() - parents.size()<<endl;	//size�Oset���������Ӽ�
		}
	}	
}
