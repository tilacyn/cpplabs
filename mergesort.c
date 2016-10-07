#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "mergesort.h"
int compare_int(void* a, void* b){
int* a1=a;
int* b1=b;
return *a1-*b1;
}

int compare_char(void* a, void* b){
char* a1=a;
char* b1=b;
return *a1-*b1;
}
int compare_str(void * str1, void * str2){
return strcmp(*(char **)str1, *(char **)str2);
}

void set_target(char *first, char *second, size_t elemsize){
size_t i = 0;
for(; i < elemsize; i++){
	*(first+i) = *(second+i);
}
}
char* merge_sort(char *up, char *down, size_t left, size_t right, size_t elemsize, int (*compare)(void*, void*))
{
if (left == right)
{
	set_target(down + elemsize * left, up + elemsize * left, elemsize);
	return down;
}

size_t middle = (left+right)/2;

char *l_buff = merge_sort(up, down, left, middle, elemsize, compare);
char *r_buff = merge_sort(up, down, middle + 1, right, elemsize, compare);
char *target = l_buff == up ? down : up;

size_t l_cur = left, r_cur = middle + 1;
size_t i = 0;
for (; i <= right; i++){
	if (l_cur <= middle && r_cur <= right){
	if ((*compare)(l_buff+l_cur*elemsize, r_buff+r_cur*elemsize) < 0){
		set_target(target + elemsize*i, l_buff + elemsize * l_cur, elemsize);
		l_cur++;
}else{
	set_target(target + elemsize*i, r_buff + elemsize * r_cur, elemsize);
	r_cur++;
	}
}
else if (l_cur <= middle){
	set_target(target + elemsize*i, l_buff + elemsize * l_cur, elemsize);
	l_cur++;
}
else{
	set_target(target + elemsize*i, r_buff + elemsize * r_cur, elemsize);
	r_cur++;
}
}
return target;
}

int mergesort(void* base, size_t num, size_t size, int (*compare)(void*, void*)){
char* temp = base;
char* buffer = malloc(size*num);
size_t left = 0;
size_t right = num-1;
char* h = merge_sort(temp, buffer, left, right, size, compare);
if(h!=temp){
    size_t j = 0;
    for(;j<num;j++){
	set_target(base+j*size, h+j*size, size);
    }
}
free(buffer);
return 0;
}
