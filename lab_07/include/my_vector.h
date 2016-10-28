#ifndef _MY_VECTOR_H_INCLUDED
#define _MY_VECTOR_H_INCLUDED
#endif
#include <cstddef>
class MyVector {
public: // methods
MyVector();
MyVector(size_t capacity);
~MyVector();
void set(size_t i, int value);
int get(size_t i);
size_t size();
size_t capacity();
void reserve(size_t new_capacity);
void resize(size_t new_size);
void push_back(int value);
void pop_back();
void insert(size_t i, int value);
void erase(size_t i);
private: // fields
std::size_t _size, _capacity;
int *_arr;
};
