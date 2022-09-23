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
			parents.clear();	//刪除set中的所有元素 
			all.clear();
			
			for(int i=0; i<n; i++){
				cin>>a>>b;
				
				parents.insert(a);	//insert不會重複插入相同數值的元素
				all.insert(a);
				all.insert(b);
			}
			
			cin>>root;
			
			cout<<all.size() - parents.size()<<endl;	//size是set中的元素個數
		}
	}	
}
