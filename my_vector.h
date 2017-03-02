#ifndef _MY_VECTOR_H_
#define _MY_VECTOR_H_
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <new>

const size_t DEFAULT_CAP = 100;

inline size_t seek_power2(const size_t cap){
    size_t x = 1;
    while(x <= cap){
        x *= 2;
    }
    return x;
}

template <class T>
class my_vector{
public:
    my_vector(){
        array_ = new T[DEFAULT_CAP];
        for(size_t i = 0; i < 100; i++){
            new (array_ + i) T();
        }
        size_ = 0;
        capacity_ = DEFAULT_CAP;
    }
    my_vector(size_t n){
        capacity_ = seek_power2(n);
        array_ = new T[capacity_];
        for(size_t i = 0; i < capacity_; i++){
            new (array_ + i) T();
        }
        size_ = 0;
	}
    my_vector(const my_vector& other){
        capacity_ = other.capacity();
        array_ = new T[capacity_];
        for(size_t i = 0; i < capacity_; i++){
            new (array_ + i) T();
        }
        for(size_t i = 0; i < capacity_; i++){
            array_[i] = other[i];
        }
        size_ = other.size();
    }
    my_vector& operator=(const my_vector& other){
        capacity_ = other.capacity();
        array_ = new T[capacity_];
        for(size_t i = 0; i < capacity_; i++){
            new (array_ + i) T();
        }
        size_ = other.size();
        return *this;
    }
    ~my_vector(){
        for(size_t i = 0; i < capacity_; i++){
            array_[i].~T();
        }
        delete[] array_;
    }

    size_t size() const{
        return size_;
    }
    size_t capacity() const{
        return capacity_;
    }
    bool empty() const{
        return size_ == 0;
    }
    void reserve(size_t n){
        size_t old_cap = capacity_;
        T* array_old = array_;
        capacity_ = seek_power2(n);
        array_ = new T[128];
        for(size_t i = 0; i < capacity_; i++){
            new (array_ + i) T();
        }
        for(size_t i = 0; i < std::min(size_, capacity_); i++){
            array_[i] = array_old[i];
        }

        for(size_t i = 0; i < old_cap; i++){
            array_old[i].~T();
        }
        delete[] array_old;
    }

    void resize(size_t n){
        if(n <= size_){
            size_ = n;
        }else{
            reserve(n);
            size_ = n;
        }
    }

    T operator[](size_t index) const{
        return array_[index];
    }
    T& operator[](size_t index){
        return array_[index];
    }

    void push_back(const T& t){
        if(size_ * 2 >= capacity_){
            reserve(size_ + 1);
        }
        array_[size_++] = t;
    }
    void pop_back(){
        size_--;
        array_[size_].~T();
    }
    void clear(){
        for(size_t i = 0; i < capacity_; i++){
            array_[i].~T();
        }
        delete[] array_;
        array_ = new T[DEFAULT_CAP];
        capacity_ = DEFAULT_CAP;
        size_ = 0;
    }

private:
    size_t capacity_;
    size_t size_;
    T* array_;
};

template <class T>
inline std::ostream& operator<<(std::ostream& stream, my_vector<T>& vec){
    for(size_t i = 0; i < vec.size(); i++){
        stream << vec[i] << " ";
    }
    return stream;
}

#endif
