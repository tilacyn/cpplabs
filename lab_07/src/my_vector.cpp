#include <iostream>
#include <stdexcept>
#include <utility>
#include <cstdio>
#include "my_vector.h"

    size_t MyVector::size(){
        return MyVector::_size;
    }

    size_t MyVector::capacity(){
        return MyVector::_capacity;
    }

    void MyVector::set(size_t i, int value){
        if(i < MyVector::_size && i > 0)
            MyVector::_arr[i] = value;
    }

    int MyVector::get(size_t i){
        return MyVector::_arr[i];
    }

    void MyVector::reserve(size_t new_capacity){
        MyVector::_capacity = new_capacity;
        int *new_arr = (int*)malloc(sizeof(int) * MyVector::_capacity);
        for (size_t i = 0; i < MyVector::_size; ++i )
            new_arr[i] = MyVector::_arr[i];

        free(MyVector::_arr);
	MyVector::_arr = new_arr;
    }



    void MyVector::resize(size_t new_size){
        MyVector::_capacity = 2 * new_size;
        int *new_arr = (int*)malloc(sizeof(int) * MyVector::_capacity);
        for (size_t i = 0; i < std::min( MyVector::_size, new_size ); ++i )
            new_arr[i] = MyVector::_arr[i];

        free(MyVector::_arr);
        MyVector::_size = new_size;
        MyVector::_arr = new_arr;
    }

    MyVector::MyVector(size_t capacity){
        MyVector::_size = 0;
        MyVector::_capacity = capacity;
        MyVector::_arr = (int*)malloc(sizeof(int) * MyVector::_capacity);
        
    }

    MyVector::MyVector(){
        MyVector::_size = 0;
        MyVector::_capacity = 2;
        MyVector::_arr = (int*)malloc(sizeof(int) * MyVector::_capacity);
    }

    MyVector::~MyVector(){
        free(MyVector::_arr);
        
    }

    void MyVector::push_back(int value){
        if ( MyVector::_size == MyVector::_capacity ){
            MyVector::resize( MyVector::_size + 1 );
            --MyVector::_size;
        }

        MyVector::_arr[MyVector::_size++] = value;
    }
    void MyVector::pop_back(){
        if(_size > 0)
            _size--;
    }
    void MyVector::erase(size_t i){
        for(; i < MyVector::_size - 1; i++){
            MyVector::_arr[i] = MyVector::_arr[i + 1];
        }
        MyVector::_size--;
    }


    void MyVector::insert(size_t i, int value){
        if(MyVector::_size + 1 > MyVector::_capacity){
            MyVector::resize(MyVector::_size + 1);
        }
        else{
            MyVector::_size += 1;
        }
        for(size_t j = _size - 1; j > i; j--){
            MyVector::_arr[j] = MyVector::_arr[j - 1];
        }
        MyVector::_arr[i] = value;
    }
