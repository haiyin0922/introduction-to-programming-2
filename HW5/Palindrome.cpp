//#include "function.h"
#include <iostream>
using namespace std;

class SimpleString
{
    friend std::ostream &operator<<(std::ostream &, const SimpleString &);
    friend std::istream &operator>>(std::istream &, SimpleString &);
public:
    SimpleString():size(0),ptr(NULL){} // default constructor
    SimpleString( const SimpleString & ); // copy constructor
    ~SimpleString(); // destructor
    const SimpleString &operator=( const SimpleString & ); // assignment operator
    bool operator==( const SimpleString & ) const; // equality operator
    void reverse(); // reverse the string
private:
    size_t size; // pointer-based string size
    char *ptr; // pointer to first element of pointer-based string
}; // end class SimpleString

class PalindromeChecker
{
public:
    PalindromeChecker(const SimpleString &s)
    {
		str = s;
        rev = s;
        rev.reverse();
    };
    void isPalindrome()
    { 
		if(rev == str)
            std::cout << "Yes\n";
        else
            std::cout << "No\n";    
    };
private:
    SimpleString str;
    SimpleString rev;
};

ostream &operator<<(ostream &output, const SimpleString &s)
{
	output<<s.ptr;
	
	return output;
} 

istream &operator>>(istream &input, SimpleString &s)
{
	s.ptr = new char[100000];
	input>>s.ptr;
	
	for(size_t i=0; ; i++){
		if(s.ptr[i]==NULL){
			s.size = i;
			break;
		}
	}
	
	return input;
}    
	
SimpleString::SimpleString( const SimpleString &s ) // copy constructor
{
	ptr = new char [s.size];
	size = s.size;
	
	for(size_t i=0; i<s.size; i++){
		ptr[i] = s.ptr[s.size-i-1]; 
	}
}

SimpleString::~SimpleString() // destructor
{
	delete[] ptr;
}
 
const SimpleString& SimpleString::operator=( const SimpleString &s) // assignment operator
{
	ptr = new char[s.size];
	size = s.size;
	
	for(size_t i=0; i<s.size; i++){
		ptr[i] = s.ptr[s.size-i-1];
	}
	
	return *this;
}
 
bool SimpleString::operator==( const SimpleString &s ) const // equality operator
{
	for(size_t i=0; i<s.size; i++){
		if(ptr[i] != s.ptr[s.size-i-1])
			return false;
	}
	
	return true;
}

void SimpleString::reverse() // reverse the string
{	
	SimpleString tmp(*this);
	
	for(size_t i=0; i<size; i++){
		ptr[i] = tmp.ptr[size-i-1];
	}
}	 

int main()
{
    SimpleString s;
    
    while(cin>>s){
    	
        if(cin.eof())break;
        
        PalindromeChecker c(s);
        c.isPalindrome();
        
		cout<<s<<endl;
    }

    return 0;
}
