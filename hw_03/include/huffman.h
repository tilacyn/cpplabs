#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_

#include <map>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <deque>
#include <cstring>
#include <string>
#include <fstream>
#include "stdint.h"
#include <cstddef>
#include <stdexcept>
#include <sstream>

class TreeNode{
public:
    int pos;
    bool flag;
    bool get_flag(){return flag;}
    uint8_t c;
    int cur;
    int left, right, par;
};

bool compare1(const TreeNode& f, const TreeNode& s);
	



class HuffTree{
private:
    std::vector <TreeNode> tree;
    std::vector <TreeNode> source;
    int ptr;
public:
    TreeNode& get_top();
    std::vector <TreeNode>& get_tree();
    std::vector <TreeNode>& get_source();
    void push_source(const TreeNode& node);
    void push_tree(const TreeNode& node);
    void sort();
    void make_tree();
};

class HuffmanArchiver{
private:
    long long archive_size;
    long long symcount;
    int table_len;
    std::map <uint8_t, int> currency;
    HuffTree htree;
    std::map <uint8_t, std::string> codes;
    std::map <std::string, uint8_t> cypher;
public:
    long long get_archive_size();
    long long get_symcount();
    int get_table_len();
    TreeNode& get_top();
    void go(TreeNode& symbol, std::string cs);
    void count_currency(std::istream& ifs);
    void sort_source();
    void make_tree();
    void write_table(std::ostream& ofs);
    void encode(std::istream& ifs, std::ostream& ofs);
    void decode(std::istream& ifs, std::ostream& ofs);
};

#endif
