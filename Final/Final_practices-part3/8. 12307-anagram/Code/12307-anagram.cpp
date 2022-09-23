/**
 * NTHUOJ: 12307 - anagram
 * (https://acm.cs.nthu.edu.tw/problem/12307/)
 * Note: C++11 needed.
 */

#include <iostream>
#include <cctype>
#include <string>
#include <algorithm>
#include <map>
#include <set>

std::map<std::string, std::string> strMap;
std::set<std::string> uniSet;

/**
 * The function is used to analyze the character relationship in a string.
 * It transforms the string to lowercase and sorts characters alphabetically.
 * @para str
 *          the string intended to be analyzed
 * @return
 *          the sorted character list as string
 */
std::string Transform(std::string str)
{
    std::string ls;
    // change to lower case
    //ls.resize(str.length());
    for(char c : str)
        ls.push_back(std::tolower(c));
    // sort character list
    std::sort(ls.begin(), ls.end());
    return ls;
}

/**
 * Find if 'ls' exists. If yes, then s is not a unique string. Remove it from unique set.
 * If no, then s is a new unique string, add s into unique set and update charset pool info.
 * @para s
 *			the original string
 * @para ls
 *			the charset of s
 */
void findAnagram(std::string &s, std::string &ls)
{
	auto iter = strMap.find(ls);    // find if ls already existed
	if(iter!=strMap.end()){
		// if existed, it has anagram. Remove from unique set.
		uniSet.erase((*iter).second);
	}else{
		// if no, add the unique string and update search map.
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
