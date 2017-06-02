#include "autotest.h"
#include "huffman_test.h"


int main(){
    TestHuffman th;
    th.runAllTests();
    TestHuffman::print();
    return 0;
}
