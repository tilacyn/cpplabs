#ifndef _HUFFMAN_TEST_H_
#define _HUFFMAN_TEST_H_


#include "autotest.h"


class TestHuffman : public Test{
public:
    void test_table_len();
    void test_nbytes();
    void runAllTests(){
        test_table_len();
        test_nbytes();
    }
};

#endif
