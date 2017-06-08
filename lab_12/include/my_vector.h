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
    while(x < cap){
        x *= 2;
    }
    return x;
}

template <typename T>
class my_vector{
public:
    my_vector(){
        //std::cout << "WOWOW\n";
        array_ = (T*) new char[sizeof(T) * DEFAULT_CAP];
        //std::cout << "WOWOW\n";
        for(size_t i = 0; i < DEFAULT_CAP; i++){
            new (array_ + i) T();
        }
        size_ = 0;
        capacity_ = DEFAULT_CAP;
    }
    my_vector(size_t n){
        capacity_ = seek_power2(n);
        array_ = (T*) new char[capacity_ * sizeof(T)];
        for(size_t i = 0; i < capacity_; i++){
            new (array_ + i) T();
        }
        size_ = 0;
	}
    my_vector(const my_vector& other){
        capacity_ = other.capacity();
        array_ = (T*) new char[capacity_ * sizeof(T)];
        for(size_t i = 0; i < capacity_; i++){
            new (array_ + i) T();
        }
        size_ = other.size();
        for(size_t i = 0; i < size_; i++){
            array_[i] = other[i];
        }
    }
    my_vector& operator=(const my_vector& other){
        capacity_ = other.capacity();
        array_ = (T*) new char[capacity_ * sizeof(T)];
        for(size_t i = 0; i < capacity_; i++){
            new (array_ + i) T();
        }
        size_ = other.size();
        for(size_t i = 0; i < size_; i++){
            array_[i] = other[i];
        }
        return *this;
    }
    ~my_vector(){
        for(size_t i = 0; i < capacity_; i++){
            array_[i].~T();
        }
        delete[] (char*) array_;
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
		size_ = std::min(size_, capacity_);
        array_ = (T*) new char[capacity_ * sizeof(T)];
        for(size_t i = 0; i < capacity_; i++){
            new (array_ + i) T();
        }
        for(size_t i = 0; i < size_; i++){
            array_[i] = array_old[i];
        }

        for(size_t i = 0; i < old_cap; i++){
            array_old[i].~T();
        }
        delete[] (char*)array_old;
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
        //std::cout << capacity_ << " " << size_ << "\n";
        if(size_ * 2 >= capacity_){
            reserve(2 * capacity_);
        }
        array_[size_++] = t;
    }
    void pop_back(){
        size_--;
    }
    void clear(){
        for(size_t i = 0; i < capacity_; i++){
            array_[i].~T();
        }
        delete[] (char*) array_;
        array_ = (T*) new char[DEFAULT_CAP * sizeof(T)];
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

