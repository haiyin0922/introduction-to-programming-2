#include<cassert>
#include<iostream>
#include <set>
//#include"function.h"
#include<cstddef>
#include<map>
#include<string>

namespace oj
{
	struct String
	{
		std::string str;
		String(const std::string &);
		String(const String &);
		String& operator=(const String &);
	};

	std::ostream& operator<<(std::ostream &,const String &);

	void insert(std::map<int,String> &ma,int key,const std::string &str);
	void output(const std::map<int,String> &ma,int begin,int end);
	void erase(std::map<int,String> &ma,int begin,int end);

	std::ostream& operator<<(std::ostream &,const std::map<int,String> &);
}

namespace oj
{
	String::String(const std::string &str_)
		:str(str_){}

	String::String(const String &rhs)
		:str(rhs.str){}

	String& String::operator=(const String &rhs)
	{
		str=rhs.str;
		return *this;
	}

	std::ostream& operator<<(std::ostream &os,const String &str)
	{
		return os<<str.str;
	}
}

namespace oj
{
    void insert(std::map<int,String> &ma,int key,const std::string &str){
        auto test=ma.find(key);
        std::string tmp;
        if(test!=ma.end()){
            tmp=str+test->second.str;
            ma.erase(test);
        }
        else
            tmp=str;

        ma.insert(std::pair<int,String>(key,String(tmp)));
    }

    void output(const std::map<int,String> &ma,int begin,int end){
        for (auto i:ma){
            if(i.first>=begin&&i.first<=end)
                std::cout<<i.second<<' ';
        }
    }

    void erase(std::map<int,String> &ma,int begin,int end){
        std::set<int> eraseKeys;
        for (auto i:ma){
            if(i.first>=begin&&i.first<=end)
                eraseKeys.insert(i.first);
        }

        for(auto key:eraseKeys){
            ma.erase(key);
        }
    }

    std::ostream& operator<<(std::ostream &o,const std::map<int,String> &ma){
        for (auto i:ma){
            o<<i.second<<' ';
        }

        return o;
    }
}

int main()
{
	using namespace std;
	using namespace oj;
	map<int,String> ma;
	for(string cmd;cin>>cmd;)
	{
		if(cmd=="insert")
		{
			int key;
			cin>>key>>cmd;
			insert(ma,key,cmd);
		}
		else
			if(cmd=="range")
			{
				int begin,end;
				cin>>cmd>>begin>>end;
				if(cmd=="output")
					output(ma,begin,end);
				else
					if(cmd=="erase")
						erase(ma,begin,end);
					else
						assert(false);
			}
			else
				assert(false);
		cout<<ma<<endl;
	}
}
