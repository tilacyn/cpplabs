#include "huffman_test.h"

void TestHuffman::test_table_len(){
    HuffmanArchiver ha;
    std::stringstream ifs("kek");
    std::ofstream ofs("tmp");
    ha.count_currency(ifs);
    ha.make_tree();
    ha.go(ha.get_top(), "");
    ha.write_table(ofs);
    ifs.seekg(0);
    ha.encode(ifs, ofs);
    checkf(12 == ha.get_table_len(), "test_table_len failed\n");
}


void TestHuffman::test_nbytes(){
    HuffmanArchiver ha;
    std::stringstream ifs("Wowowowowowowow");
    std::ofstream ofs("tmp");
    ha.count_currency(ifs);
    ha.make_tree();
    ha.go(ha.get_top(), "");
    ha.write_table(ofs);
    ifs.seekg(0);
    ha.encode(ifs, ofs);
    checkf(15 == ha.get_symcount(), "test_nbytes failed\n");
}
