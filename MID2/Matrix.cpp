#include <iostream>
//#include "function.h"
using namespace std;

class Matrix
{
    friend std::ostream &operator<<(std::ostream &, const Matrix &);
    friend std::istream &operator>>(std::istream &, Matrix &);
public:
    Matrix(int s = 5);
    Matrix(const Matrix &);// copy constructor
    ~Matrix();
    Matrix &operator=(const Matrix &a);
    Matrix &clockwise90();
private:
    int **matrix;
    int *buf;   // 2D matrix stored in 1D raster scan order
    int size;
}; //end class Matrix

ostream &operator<<(ostream &output, const Matrix &a)
{
	for(int i=0; i<a.size; i++){
		for(int j=0; j<a.size; j++){
			output<<a.matrix[i][j];
			if(j<a.size-1) output<<" ";
		}
		output<<endl;
	}
	
	return output;
}

istream &operator>>(istream &input, Matrix &a)
{
	for(int i=0; i<a.size; i++){
		for(int j=0; j<a.size; j++){
			input>>a.matrix[i][j];
		}
	}

	return input;
}

Matrix::Matrix(int s)
{
	matrix = new int*[s];
	for(int i=0; i<s; i++){
		matrix[i] = new int[s];
	}
	
	size = s;
} 

Matrix::Matrix(const Matrix &a)// copy constructor
{
	matrix = new int*[a.size];
	for(int i=0; i<a.size; i++){
		matrix[i] = new int[a.size];
	}
	
	*this = a;
}

Matrix::~Matrix()
{
	for(int i=0; i<size; i++)
   		delete []matrix[i];
   	delete []matrix;
}

Matrix &Matrix::operator=(const Matrix &a)
{
	for(int i=0; i<a.size; i++){
		for(int j=0; j<a.size; j++){
			matrix[i][j] = a.matrix[i][j];
		}
	}
	size = a.size;
	
	return *this;
}

Matrix &Matrix::clockwise90()
{
	Matrix copy(*this);
	
	for(int i=0; i<size; i++){
		for(int j=0; j<size; j++){
			matrix[i][j] = copy.matrix[size-j-1][i];
		}
	}
	
	return *this; 
} 

int main()
{
    int matrix_size;
    cin>>matrix_size;

    Matrix a(matrix_size);
    cin>>a;

    cout<<endl;
    cout<<a.clockwise90().clockwise90()<<endl;
    cout<<a<<endl;

    return 0;
} // end main
