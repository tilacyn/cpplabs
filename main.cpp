#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include "my_vector.h"

using namespace std;

class Product {
public:
    void namecpy(const char* s){
        name_ = new char[strlen(s)];
        strcpy(name_, s);
    }
    Product(){
        name_ = new char[10];
        quantity_ = 0;
        price_ = 0;
    }
    Product(const Product& other){
        namecpy(other.name_);
        quantity_ = other.quantity_;
        price_ = other.price_;
    }
    Product& operator=(const Product& other){
        namecpy(other.name_);
        quantity_ = other.quantity_;
        price_ = other.price_;
        return *this;
    }
    Product(const char* name, int quantity, double price){
		namecpy(name);
		quantity_ = quantity;
		price_ = price;
    }
    char* name(){ return name_;}
    int quantity(){ return quantity_;}
    double price(){ return price_;}
    friend std::ostream& operator<<(std::ostream& stream, const Product& p){
        int i = 0;
        do{
            stream << p.name_[i++];
        }while(p.name_[i - 1] != '\0');
        stream << p.quantity_ << " " << p.price_;
        return stream;
    }

private:
    char *name_;
    int quantity_;
    double price_;
};

void print(my_vector<Product>& v) {
   	std::cout << v << std::endl;
}
/*
template<typename T>
void test_my_vector(const T& a, const T& b){
        my_vector<T> v(2);
        my_vector<T> v2();
        my_vector<T> v3(v);
        assert(v3.size() == v.size() && v3.capacity() == v.capacity());
 //       assert(v.size() == 0 && v.capacity() == 2);
        cout << "push_back" << endl;
        v.push_back(a);
        v.push_back(b);
        v.pop_back();
   		cout << "clear" << endl;
        v.clear();
        cout << "done" << endl;
        assert(v.empty());
        cout << "1" << endl;
        v.push_back(a);
        cout << "2" << endl;
        v.push_back(a);
        cout << "reserve" << endl;
        v.reserve(5);
        cout << "resize" << endl;
        assert(v.size() == 2 && v.capacity() == 8);
        v.resize(5);
        assert(v.size() == 5 && v.capacity() == 8);
}
*/


template <class T>
void test_my_vector(const T& a, const T& b){
	my_vector <T> arr;
	arr.push_back(a);
	arr.push_back(b);
	assert(arr.size() == 2);
	arr.pop_back();
	assert(arr.size() == 1);
	arr.clear();
	assert(arr.empty());
	for(size_t t = 0; t < 10; t++){
		t % 2 == 0 ? arr.push_back(a) : arr.push_back(b);
	}
	my_vector <T> arr1 = arr;
	my_vector <T> arr2(arr1);
	my_vector <T> arr3(3);
	arr3.push_back(a);
    arr3.push_back(a);
    arr3.push_back(b);
    assert(arr3.size() == 3);
	std::cout << arr1 << "\n";
    T tmp = arr[arr1.size() - 1];
    arr2.push_back(tmp);
    arr2[0] = a;
    assert(arr1.size() == arr2.size() - 1);
	assert(arr1.capacity() == arr2.capacity());
	assert(!arr.empty());
    arr.resize(15);
    arr1.resize(3);
    arr2.reserve(50);
    assert(arr2.capacity() == 64);
    assert(arr.size() == 15);
    assert(arr1.size() == 3);
}


int main() {
    test_my_vector<int>(5, 10);
    test_my_vector<Product>(Product("asdf", 4, 12.0), Product("qwe", -1, 7.5));
	test_my_vector<int>(4, 3);
	test_my_vector<Product>(Product("kek", 50, 5), Product("lol", 40, 4));
    return 0;
}
