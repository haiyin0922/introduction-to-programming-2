#include <iostream>
#include <cctype>
#include <string>
#include <algorithm>
#include <map>
#include <set>

std::map<std::string, std::string> strMap;
std::set<std::string> uniSet;

std::string Transform(std::string str)
{
    std::string ls;
    for(char c : str)
        ls.push_back(std::tolower(c));
    std::sort(ls.begin(), ls.end());
    return ls;
}

void findAnagram(std::string &s, std::string &ls)
{
	auto iter = strMap.find(ls);    // find if ls already existed
	if(iter!=strMap.end()){
		uniSet.erase(iter->second);
	}else{
		uniSet.insert(s);
		strMap[ls] = s;
	}
}

int main()
{
    int n;
    std::cin >> n;
    while(n--){
        // input strings
        std::string s, ls;
        std::cin >> s;

        ls = Transform(s);
        findAnagram(s, ls);
    }

    // output uniSet strings
    for(auto s : uniSet){
        std::cout << s << std::endl;
    }
    return 0;
}
