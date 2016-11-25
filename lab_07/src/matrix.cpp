#include "../include/matrix.h"
#include <iostream>
#include <stdexcept>
#include <utility>
#include <cstdio>
using std::cout; // пространство имен std для cout
using std::cin; // пространство имен std для cin
 
#include <iomanip> // для манипулятора setw
using std::setw;   // пространство имен std для setw
 
#include <cstdlib>
 
Matrix::Matrix(const std::size_t r, const std::size_t c)
{
	_rows = r;
	_cols = c;
	_data = (int**) malloc(sizeof(int*) * r);
	for(unsigned int i = 0; i < r; i++){
		_data[i] = (int*)malloc(sizeof(int) * c);
	}
}

Matrix::Matrix(const Matrix& m)
{
	*this = m;
}


void Matrix::print(FILE *f) const{
	for(unsigned int i = 0; i < _rows; i++){
		fwrite(_data[i], 4, _cols, f);
	}
}

void Matrix::wow_print() const{
	for(unsigned int i = 0; i < _rows; i++){
		for(unsigned int j = 0; j < _cols; j++){
			printf("%d ", _data[i][j]);
		}
		printf("\n");
	}
}

std::size_t Matrix::get_rows() const{
	return _rows;
}

std::size_t Matrix::get_cols() const{
	return _cols;
}
void Matrix::set(const std::size_t i, const std::size_t j, const int val){
	_data[i][j] = val;
}
 
int Matrix::get(const std::size_t i, const std::size_t j) const{
	return _data[i][j];
}

Matrix Matrix::operator+ (const Matrix &m) const{
    Matrix result(_rows, _cols);
    for (unsigned int i = 0; i < _rows; i++)
        for (unsigned int j = 0; j < _cols; j++)
            result._data[i][j] = _data[i][j] + m._data[i][j];
 
    return result;
}
 
Matrix& Matrix::operator+= (const Matrix &m){
	for (unsigned int i = 0; i < _rows; i++)
		for (unsigned int j = 0; j < _cols; j++)
	            	_data[i][j] += m._data[i][j];
    return *this;
}

Matrix& Matrix::operator-= (const Matrix &m){
	for (unsigned int i = 0; i < _rows; i++)
		for (unsigned int j = 0; j < _cols; j++)
	            	_data[i][j] -= m._data[i][j];
    return *this;
}
 
Matrix Matrix::operator-(const Matrix &m) const{
    	Matrix result(_rows, _cols);
    	for (unsigned int i = 0; i < _rows; i++)
    	    	for (unsigned int j = 0; j < _cols; j++)
    		        result._data[i][j] = _data[i][j] - m._data[i][j];
    	return result;
}
 
 
const Matrix& Matrix::operator= (const Matrix &m){
    	_rows = m._rows;
	_cols = m._cols;
	if(this)
		free(_data);
	_data = (int**)malloc(sizeof(int*) * _rows);
	for(unsigned int i = 0; i < _rows; i++){
		_data[i] = (int*)malloc(sizeof(int) * _cols);
	}
	for(unsigned int i = 0; i < _rows; i++){
		for(unsigned int j = 0; j < _cols; j++){
			_data[i][j] = m._data[i][j];
		}
	}
    return *this; 
}
 
bool Matrix::operator== (const Matrix &m)const {
	for(unsigned int i = 0; i < _rows; i++){
		for(unsigned int j = 0; j < _cols; j++){
			if(_data[i][j] != m._data[i][j])
				return false;
		}
	}
	return true;
}

bool Matrix::operator!= (const Matrix &m)const {
	for(unsigned int i = 0; i < _rows; i++){
		for(unsigned int j = 0; j < _cols; j++){
			if(_data[i][j] != m._data[i][j])
				return true;
		}
	}
	return false;
}

Matrix Matrix::operator*(const Matrix& m)const {
	Matrix result(_rows, m._cols);
	for(unsigned int i = 0; i < result._rows; i++){
		for(unsigned int j = 0; j < result._cols; j++){
			result._data[i][j] = 0;
			for(unsigned int k = 0; k < _cols; k++){
				result._data[i][j] += _data[i][k] * m._data[k][j];
			}
		}
	}
	return result;
}

Matrix& Matrix::operator*=(const Matrix& m) {
	Matrix result(_rows, m._cols);
	for(unsigned int i = 0; i < result._rows; i++){
		for(unsigned int j = 0; j < result._cols; j++){
			result._data[i][j] = 0;
			for(unsigned int k = 0; k < _cols; k++){
				result._data[i][j] += _data[i][k] * m._data[k][j];
			}
		}
	}
	*this = result;
	return *this;
}


