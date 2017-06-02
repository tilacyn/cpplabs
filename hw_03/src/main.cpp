#include "..\include\huffman.h"


using namespace std;

void encode(const char* in_filename, const char* out_filename){
    HuffmanArchiver ha;
    if(out_filename == NULL) throw runtime_error("No filename/key given\n");
    std::ifstream ifs(in_filename, ios::binary); // уг
    std::ofstream ofs_hcode(out_filename, ios::binary);
    if(!ifs.is_open()){
        throw runtime_error("FATAL ERROR\nNo such file in the directory\n");
    }
    ha.count_currency(ifs);
    ha.make_tree();
    ha.go(ha.get_top(), "");
    ha.write_table(ofs_hcode);
    ifs.seekg(0);
    ha.encode(ifs, ofs_hcode);
    cout << ha.get_symcount() << "\n" << ha.get_archive_size() << "\n" << ha.get_table_len() << "\n";
}

void decode(const char* in_filename, const char* out_filename){
    HuffmanArchiver ha;
    if(in_filename == NULL) throw runtime_error("No filename/key given\n");
    std::ifstream ifs_hcode(in_filename, ios::binary);
    if(!ifs_hcode.is_open()){
        throw runtime_error("FATAL ERROR\nNo such file in the directory\n");
    }
    std::ofstream res_file(out_filename, ios::binary);
    ha.decode(ifs_hcode, res_file);
    cout << ha.get_symcount() << "\n" << ha.get_archive_size() << "\n" << ha.get_table_len() << "\n";
}

int main(int argc, char* argv[]){
    int archive_mode = 0;
    bool infile = false;
    bool outfile = false;
    char* in_filename = NULL;
    char* out_filename = NULL;
    for(int i = 0 ; i < argc; i++){
        if(infile){
            in_filename = new char[100];
            strcpy(in_filename, argv[i]), infile = false;
            continue;
        }
        if(outfile){
            out_filename = new char[100];
            strcpy(out_filename, argv[i]), outfile = false;
            continue;
        }
        if(!strcmp(argv[i], "-f")){
            infile = true;
            continue;
        }
        if(!strcmp(argv[i], "-o")){
            outfile = true;
            continue;
        }
        if(!strcmp(argv[i], "-c")){
            archive_mode = 1;
            continue;
        }
        if(!strcmp(argv[i], "-u")){
            archive_mode = 2;
            continue;
        }
    }
    try{
        if(archive_mode == 1){
            encode(in_filename, out_filename);
        } else if(archive_mode == 2){
            decode(in_filename, out_filename);
        } else throw runtime_error("No targets given\n");
    } catch(runtime_error& re){
        cout << re.what();
    }
    return 0;
}
