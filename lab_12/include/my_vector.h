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
        array_ = (T*) new char[sizeof(T) * DEFAULT_CAP];
        size_ = 0;
        capacity_ = DEFAULT_CAP;
    }
    my_vector(size_t n){
        capacity_ = seek_power2(n);
        array_ = (T*) new char[capacity_ * sizeof(T)];
        for(size_t i = 0; i < n; i++){
            new (array_ + i) T();
        }
        size_ = n;
	}
    my_vector(const my_vector& other){
        capacity_ = other.capacity();
        size_ = other.size();
        array_ = (T*) new char[capacity_ * sizeof(T)];
        for(size_t i = 0; i < size_; i++){
            new (array_ + i) T();
            array_[i] = other[i];
        }
    }
    my_vector& operator=(const my_vector& other){
        for(size_t i = 0; i < size_; i++){
            array_[i].~T();
        }
        delete[] (char*) array_;
        capacity_ = other.capacity();
        size_ = other.size();
        array_ = (T*) new char[capacity_ * sizeof(T)];
        for(size_t i = 0; i < size_; i++){
            new (array_ + i) T();
            array_[i] = other[i];
        }
        return *this;
    }
    ~my_vector(){
        for(size_t i = 0; i < size_; i++){
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
        T* array_old = array_;
        capacity_ = seek_power2(n);
		array_ = (T*) new char[capacity_ * sizeof(T)];
        for(size_t i = 0; i < size_; i++){
            new (array_ + i) T();
            array_[i] = array_old[i];
            array_old[i].~T();
        }
        delete[] (char*)array_old;
    }

    void resize(size_t n){
        if(n <= size_){
            while(size_ > n){
                array_[--size_].~T();
            }
        }else{
            reserve(n);
            for(size_t i = size_; i < n; i++){
                new (array_ + i) T();
            }
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
            reserve(2 * capacity_);
        }
        new (array_ + size_) T();
        array_[size_++] = t;
    }
    void pop_back(){
        array_[--size_].~T();
    }
    void clear(){
        std::cout << size_ << "\n";
        for(size_t i = 0; i < size_; i++){
            array_[i].~T();
        }
        std::cout << size_ << "\n";
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
inline std::ostream& operator<<(std::ostream& stream, const my_vector<T>& vec){
    for(size_t i = 0; i < vec.size(); i++){
        if(i == vec.size() - 1) stream << vec[i];
        else stream << vec[i] << " ";
    }
    return stream;
}

#endif
