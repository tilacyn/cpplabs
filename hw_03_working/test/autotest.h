#ifndef _AUTOTEST_H_
#define _AUTOTEST_H_


#include "..\include\huffman.h"

class Test{
private:
    static unsigned int n_failed;
    static unsigned int n_passed;
public:
    static void checkf(bool expr, std::string s);
    virtual void runAllTests();
    static void print();
};

#endif
