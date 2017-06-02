#include "autotest.h"
#include "huffman_test.h"

unsigned int Test::n_passed = 0;
unsigned int Test::n_failed = 0;

void Test::checkf(bool expr, std::string s){
    if(!expr){
        n_failed++;
        std::cout << s;
    } else n_passed++;
}

void Test::print(){
    if(n_failed == 0 && n_passed == 0){
        std::cout << "No tests\n";
    }else if(!n_failed){
        std::cout << "All tests passed\n";
    } else{
        std::cout << "Only " << n_passed << " tests passed out of " << n_passed + n_failed;
    }
}
