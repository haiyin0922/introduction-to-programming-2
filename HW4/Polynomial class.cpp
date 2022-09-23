#include <iostream>
#include <stdio.h>
#include <string>
//#include "function.h"
using namespace std;

class Polynomial
{

public:
    Polynomial();
    Polynomial(const int , const int [51]);
    Polynomial add( const Polynomial) const; // add function
    Polynomial subtract( const Polynomial ) const; // subtract function
    Polynomial multiplication( const Polynomial ) const; // multiplication function
    void output() const;
private:
    int coefficients[101]; // integer coefficients
    int greatestPower; // integer greatestPower
}; // end class Polynomial

int main()
{
    int greatestPower1, greatestPower2;
    int coefficient1[51], coefficient2[51];
    Polynomial ans;

    cin>>greatestPower1;
    for(int i = greatestPower1 ; i >= 0; i--)
    {
        cin>>coefficient1[i];
    }
    cin>>greatestPower2;
    for(int i = greatestPower2 ; i >= 0 ; i--)
    {
        cin>>coefficient2[i];
    }
    Polynomial a(greatestPower1, coefficient1), b(greatestPower2, coefficient2) ;

    ans = a.add( b );
    ans.output();
    cout << endl;

    ans = a.subtract( b );
    ans.output();
    cout << endl;

    ans = a.multiplication( b );
    ans.output();
    cout << endl;

} // end main

Polynomial::Polynomial()
{
	greatestPower = 0;
	coefficients[101] = {0};
} 

Polynomial::Polynomial(const int gtpow, const int coef[51])
{
	greatestPower = gtpow;
	for(int i=greatestPower; i>=0 ; i--){
		coefficients[i] = coef[i];
	}
}
 
Polynomial Polynomial::add( const Polynomial b) const // add function
{
	Polynomial c;
	
	if(greatestPower<b.greatestPower){
		for(int i=0; i<=greatestPower; i++){
			c.coefficients[i] = coefficients[i] + b.coefficients[i];
			if(c.coefficients[i]!=0) c.greatestPower = i;
		}
		for(int i=greatestPower+1; i<=b.greatestPower; i++){
			c.coefficients[i] = b.coefficients[i];
			if(c.coefficients[i]!=0) c.greatestPower = i;
		}
	}
	else{
		for(int i=0; i<=b.greatestPower; i++){
			c.coefficients[i] = coefficients[i] + b.coefficients[i];
			if(c.coefficients[i]!=0) c.greatestPower = i;
		}
		for(int i=b.greatestPower+1; i<=greatestPower; i++){
			c.coefficients[i] = coefficients[i];
			if(c.coefficients[i]!=0) c.greatestPower = i;
		}
	}
	
	return c;
	
} 

Polynomial Polynomial::subtract( const Polynomial b) const // subtract function
{
	Polynomial c;
	
	if(greatestPower<b.greatestPower){
		for(int i=0; i<=greatestPower; i++){
			c.coefficients[i] = coefficients[i] - b.coefficients[i];
			if(c.coefficients[i]!=0) c.greatestPower = i;
		}
		for(int i=greatestPower+1; i<=b.greatestPower; i++){
			c.coefficients[i] = - b.coefficients[i];
			if(c.coefficients[i]!=0) c.greatestPower = i;
		}
	}
	else{
		for(int i=0; i<=b.greatestPower; i++){
			c.coefficients[i] = coefficients[i] - b.coefficients[i];
			if(c.coefficients[i]!=0) c.greatestPower = i;
		}
		for(int i=b.greatestPower+1; i<=greatestPower; i++){
			c.coefficients[i] = coefficients[i];
			if(c.coefficients[i]!=0) c.greatestPower = i;
		}
	}
	
	return c;
}

Polynomial Polynomial::multiplication( const Polynomial b) const // multiplication function
{
	Polynomial c;
	int mul = 0;
	
	c.greatestPower = greatestPower + b.greatestPower;
	
	for(int i=0; i<=c.greatestPower; i++){
		for(int j=i; j>=0; j--){
			if(j<=greatestPower && i-j<=b.greatestPower)
			mul += coefficients[j] * b.coefficients[i-j];
		}
		c.coefficients[i] = mul;
		mul = 0;
	}
	
	return c;
}

void Polynomial::output() const
{
	for(int i=greatestPower; i>=0; i--){
		cout<<coefficients[i];
		if(i>0) cout<<" ";
	}
}
