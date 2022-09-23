#include<iostream>
#include<string>
#include<map>
using namespace std;

main()
{
	int n;
	string name, school;
	
	map<string, string> mapName; //map<key, value>
	mapName["Wa"] = "Waninoko";
	mapName["Mi"] = "Milotic";
	mapName["Ma"] = "Magikarp";
	mapName["Va"] = "Vaporeon";
	mapName["Sh"] = "Sharpedo";
	mapName["Tapu"] = "Tapu Fini";
	mapName["Em"] = "Empoleon";
	mapName["La"] = "Lapras";
	mapName["Pi"] = "Pikachu";
	mapName["Pe"] = "Pikachu";
	mapName["Me"] = "Mega Gyarados";
	
	cin>>n;
	
	for(int i=0; i<n; i++){
		cin>>name>>school;
		
		auto it = mapName.find(name.substr(0, 4));	//find()���ɦ^�Ǹ�ƩҦb��m�A�䤣��h�^�ǻPend()��Ʀ^�ǭȬۦP //substr(�}�l, ����)
		if(it != mapName.end())
			cout<<name<<" the "<<school<<" "<<mapName[name.substr(0, 4)]<<endl;
		else{
			it = mapName.find(name.substr(0, 2));
			if(it != mapName.end())
				cout<<name<<" the "<<school<<" "<<mapName[name.substr(0, 2)]<<endl;
			else
				cout<<name<<" is looking for a Chinese tutor, too!"<<endl;
		}
	}
}
