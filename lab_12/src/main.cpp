#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include "my_vector.h"

using namespace std;

class Product {
  public:
    void namecpy(const char* s){
		//if(name_) delete[] name_;
        name_ = new char[strlen(s) + 1];
        strcpy(name_, s);
    }
    Product(){
        name_ = NULL;
        quantity_ = 0;
        price_ = 0;
    }
	~Product(){ if(name_)delete[] name_;}
    Product(const Product& other){
		//if(name_) delete[] name_;
        if(other.name_) namecpy(other.name_);
        quantity_ = other.quantity_;
        price_ = other.price_;
    }
    Product& operator=(const Product& other){
		if(other.name_) namecpy(other.name_);
        quantity_ = other.quantity_;
        price_ = other.price_;
        return *this;
    }

    Product(const char* name, int quantity, double price){
		//if(name_) delete[] name_;
		//cout << "KEKEK\n";
		if(name){
            name_ = new char[strlen(name)];
            strcpy(name_, name);
		}
		quantity_ = quantity;
		price_ = price;
    }
    friend std::ostream& operator<<(std::ostream& stream, const Product& p){
        int i = 0;
        do{
            stream << p.name_[i++];
        }while(p.name_[i - 1] != '\0');
        stream << p.quantity_ << " " << p.price_;
        return stream;
    }

private:
    char* name_;
    int quantity_;
    double price_;
};

void print(my_vector<Product>& v) {
   	std::cout << v << std::endl;
}

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
        //cout << t << "\n";
		t % 2 == 0 ? arr.push_back(a) : arr.push_back(b);
	}
	my_vector <T> arr1 = arr;
	//cout << "WOW\n";
	my_vector <T> arr2(arr1);
	my_vector <T> arr3(3);
    arr3.push_back(a);
    arr3.push_back(a);
    arr3.push_back(b);
    assert(arr3.size() == 3);
    //cout << "KEK\n";
	std::cout << arr1 << "\n";
    arr2.push_back(arr[arr.size() - 1]);
    arr2[0] = a;
    assert(arr1.size() == arr2.size() - 1);
	assert(arr1.capacity() == arr2.capacity());
	assert(!arr.empty());
    arr.resize(15);
    arr1.resize(3);
    arr2.reserve(50);
    //cout << "KEK\n";
    assert(arr2.capacity() == 64);
    assert(arr.size() == 15);
    assert(arr1.size() == 3);
}


int main() {
    test_my_vector<int>(5, 10);
    //cout << "TOP\n";
    test_my_vector<Product>(Product("asdf", 4, 12.0), Product("qwe", -1, 7.5));
	test_my_vector<int>(4, 3);
	test_my_vector<Product>(Product("kek", 50, 5), Product("lol", 40, 4));
    return 0;
}
