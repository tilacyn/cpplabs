#include "huffman.h"


TreeNode& HuffTree::get_top(){
    return tree[ptr - 1];
}

std::vector <TreeNode>& HuffTree::get_tree(){
    return tree;
}


std::vector <TreeNode>& HuffTree::get_source(){
    return source;
}


void HuffTree::push_source(const TreeNode& node){
    source.push_back(node);
}


void HuffTree::push_tree(const TreeNode& node){
    tree[ptr++] = node;
}


void HuffTree::sort(){
    std::sort(source.begin(), source.end());
}


void HuffTree::make_tree(){
    std::cout << "TREE MAKING STARTED\n";
    tree.resize(100000);
    std::deque <TreeNode> qcur1, qcur2;
    for(uint32_t i = 0; i < source.size(); i++){
        source[i].pos = source[i].c;
        qcur1.push_back(source[i]);
        tree[source[i].c] = source[i];
    }
    ptr = 1000;
    while(qcur1.size() || qcur2.size()){
        if(qcur1.size() == 1 && qcur2.empty()){
            qcur2.push_back(qcur1.front());
        }
        if(qcur2.size() == 1 && qcur1.empty()) break;
        int firstp = 1000000;
        int secondp = 1000000;
        int firsec = 1000000;
        if(qcur1.size() > 1){
            TreeNode tmp = qcur1.front();
            qcur1.pop_front();
            firstp = tmp.cur + qcur1.front().cur;
            qcur1.push_front(tmp);
        }

        if(qcur2.size() > 1){
            TreeNode tmp = qcur2.front();
            qcur2.pop_front();
            secondp = tmp.cur + qcur2.front().cur;
            qcur2.push_front(tmp);
        }
        if(qcur2.size() && qcur1.size()){
            firsec = qcur2.front().cur + qcur1.front().cur;
        }
        int mincur = std::min(firsec, std::min(firstp, secondp));
        TreeNode newsym;
        newsym.c = (uint8_t)'A';
        newsym.flag = false;
        if(mincur == firstp){
            TreeNode tmp = qcur1.front();
            qcur1.pop_front();
            newsym.cur =  tmp.cur + qcur1.front().cur;
            newsym.left = tmp.pos;
            newsym.right = qcur1.front().pos;
            tree[ptr++] = newsym;
            tree[ptr - 1].pos = ptr - 1;
            qcur1.pop_front();
        } else if(mincur == secondp){
            TreeNode tmp = qcur2.front();
            qcur2.pop_front();
            newsym.cur =  tmp.cur + qcur2.front().cur;
            newsym.left = tmp.pos;
            newsym.right = qcur2.front().pos;
            tree[ptr++] = newsym;
            tree[ptr - 1].pos = ptr - 1;
            qcur2.pop_front();
        } else if(mincur == firsec){
            newsym.cur =  qcur1.front().cur + qcur2.front().cur;
            newsym.left = qcur1.front().pos;
            newsym.right = qcur2.front().pos;
            tree[ptr++] = newsym;
            tree[ptr - 1].pos = ptr - 1;
            qcur1.pop_front(), qcur2.pop_front();
        }
        qcur2.push_back(tree[ptr - 1]);
    }
}



TreeNode& HuffmanArchiver::get_top(){
    return htree.get_top();
}
void HuffmanArchiver::go(TreeNode& symbol, std::string cs){
    if(symbol.get_flag()){
        codes[symbol.c] = cs;
    }
    else go(htree.get_tree()[symbol.right], cs + "0"), go(htree.get_tree()[symbol.left], cs + "1");
}
void HuffmanArchiver::count_currency(std::istream& ifs){
    symcount = 0;
    while(ifs.peek() != std::istream::traits_type::eof()){
        uint8_t c;
        ifs.read((char*)&c, 1);
        symcount++;
        if(currency.find(c) != currency.end()){
            currency[c]++;
        } else{
            currency[c] = 1;
            TreeNode symbol;
            symbol.c = c, symbol.cur = 1, symbol.flag = true;\
            symbol.right = 13;
            htree.push_source(symbol);
        }
    }
    std::cout << "Currency counted\n";
}


void HuffmanArchiver::sort_source(){
    htree.sort();
}


void HuffmanArchiver::make_tree(){
    sort_source();
    htree.make_tree();
    std::cout << "Tree made\n";
}


void HuffmanArchiver::write_table(std::ostream& ofs){
    table_len = 0;
    for(uint32_t i = 0; i < htree.get_source().size(); i++){
        table_len += 5;
        table_len += codes[htree.get_source()[i].c].length();
    }
    std::cout << "Table len: " << table_len << "\n";
    ofs.write((char*)&table_len, 4);
    for(uint32_t i = 0; i < htree.get_source().size(); i++){
        ofs.write((char*)&(htree.get_source()[i].c), 1);
        int lenc = codes[htree.get_source()[i].c].length();
        ofs.write((char*)&lenc, 4);
        for(uint32_t j = 0; j < codes[htree.get_source()[i].c].length(); j++){
            uint8_t bytik;
            if(codes[htree.get_source()[i].c][j] - '0'){
                bytik = 1;
            } else bytik = 0;
            ofs.write((char*)&bytik, 1);
        }
    }
}

void HuffmanArchiver::encode(std::istream& ifs, std::ostream& ofs){
    std::cout << "Encoding Started\n";
    int nbytes = 0;
    uint8_t wbyte = 0;
    int wbit = 7;
    ofs.write((char*)&symcount, 4);
    while(ifs.peek() != std::istream::traits_type::eof()){
        uint8_t c;
        ifs.read((char*)&c, 1);
        for(uint32_t i = 0; i < codes[c].length(); i++){
            if(codes[c][i] - '0') wbyte |= (uint8_t)(1 << wbit);
            wbit--;
            if(wbit < 0){
                nbytes++;
                ofs.write((char*)&wbyte, 1);
                wbyte = 0;
                wbit = 7;
            }
        }
        if(ifs.peek() == std::istream::traits_type::eof()){
            if(wbit < 7){
                ofs.write((char*)&wbyte, 1);
            }
        }
    }
}

int HuffmanArchiver::get_symcount(){
    return symcount;
}

int HuffmanArchiver::get_table_len(){
    return table_len;
}

void HuffmanArchiver::decode(std::istream& ifs, std::ostream& ofs){
    std::cout << "Decoding Started\n";
    ifs.read((char*)&table_len, 4);
    std::cout << "Table len: " << (int) table_len  << "\n";
    int byte_count = 0;
    while(byte_count < table_len){
        uint8_t c;
        ifs.read((char*)&c, 1);
        int slen;
        std::string s = "";
        ifs.read((char*)&slen, 4);
        for(int i = 0; i < slen; i++){
            uint8_t next;
            ifs.read((char*)&next, 1);
            if(next == 1) s += "1";
            else s += "0";
        }
        cypher[s] = c;
        byte_count += 5 + slen;
    }
    ifs.read((char*)&symcount, 4);
    std::cout << "Symcount: " << symcount << "\n";
    int j = 7;
    int rbyte = 0;
    ifs.read((char*)&rbyte, 1);
    std::string s = "";
    int ccount = 0;
    while(ifs.peek() != std::istream::traits_type::eof() || ccount < symcount){
        if(cypher.find(s) != cypher.end()){
            ccount++;
            ofs.write((char*)&(cypher[s]), 1);
            s = "";
        }
        if(j < 0) j = 7, ifs.read((char*)&rbyte, 1);
        if(rbyte & (1 << j)){
            s += "1";
        } else s += "0";
        j--;
    }
}

