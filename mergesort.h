#include <stddef.h>
char* merge_sort(char *up, char *down, size_t left, size_t right, size_t elemsize, int (*compare)(void*, void*));
int mergesort (void* base, size_t num, size_t size, int (*compare)(void*, void*));
int compare_int(void* a, void* b);
int compare_char(void* a, void* b);
int compare_str(void * str1, void * str2);
