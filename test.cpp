#include <gtest/gtest.h>
#include "huffman.h"

TEST(HuffTree, sort_source){
	HuffTree ht;
	for(int i = 0; i < 5; i++){
		TreeNode tn;
		tn.cur = 5 - i;
		tn.c = '0' + i;		
		ht.push_source(tn);
	}
	ht.sort();
	for(int i = 0; i < ht.get_source().size() - 1; i++){
		ASSERT_TRUE(ht.get_source()[i].cur <= ht.get_source()[i + 1].cur);
	}
}

void go(TreeNode& symbol, HuffTree& ht){
	if(!symbol.get_flag()){
		ASSERT_EQ(symbol.cur, ht.get_tree()[symbol.right].cur + ht.get_tree()[symbol.left].cur);
		go(ht.get_tree()[symbol.right], ht);
		go(ht.get_tree()[symbol.left], ht);
	}
}

TEST(HuffTree, make_tree){
	HuffTree ht;
	for(int i = 0; i < 5; i++){
		TreeNode tn;
		tn.flag = true;
		tn.cur = 5 - i;
		tn.c = '0' + i;		
		ht.push_source(tn);
	}
	ht.sort();
	ht.make_tree();
	go(ht.get_top(), ht);
}

void encode_decode(){
	HuffmanArchiver ha_encode;
	std::ifstream ifs("tmp_test_source", std::ios::binary);
	std::ofstream ofs_hcode("tmp_test_archive", std::ios::binary);
	ha_encode.count_currency(ifs);
    	ha_encode.make_tree();
    	ha_encode.go(ha_encode.get_top(), "");
    	ha_encode.write_table(ofs_hcode);
	ifs.seekg(0);
    	ha_encode.encode(ifs, ofs_hcode);
	ifs.close();
	ofs_hcode.close();
	std::ofstream ofs1("tmp_test_res", std::ios::binary);
	std::ifstream ifs1("tmp_test_archive", std::ios::binary);
	HuffmanArchiver ha_decode;
	ha_decode.decode(ifs1, ofs1);
	ofs1.close();
	ifs1.close();
	ASSERT_FALSE(system("diff -s tmp_test_res tmp_test_source"));
	system("rm -rf tmp_test_res");
	system("rm -rf tmp_test_source");
	system("rm -rf tmp_test_archive");
}

TEST(HuffmanArchiver, diff_1_sym){
	std::ofstream ofs("tmp_test_source", std::ios::binary);
	ofs << "a";
	ofs.close();
	encode_decode();
}


TEST(HuffmanArchiver, diff_big_file_1_sym){
	std::ofstream ofs("tmp_test_source", std::ios::binary);
	for(int i = 0; i < 1000000; i++) ofs << (char) ('a');
	ofs.close();
	encode_decode();
}

TEST(HuffmanArchiver, diff_big_file){
	std::ofstream ofs("tmp_test_source", std::ios::binary);
	for(int i = 0; i < 1000000; i++) ofs << (char) ('a' + i % 32);
	ofs.close();
	encode_decode();
}


int main(int argc, char** argv){
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

