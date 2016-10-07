#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "mergesort.h"
int main(int argc, char *argv[]){

	int (*cmp_int)(void*, void*);
	int (*cmp_char)(void*, void*);
	int (*cmp_str)(void*, void*);
	cmp_int = &compare_int;
	cmp_char = &compare_char;
	cmp_str = &compare_str;
	if(argc>2){
		if(strcmp("int", argv[1]) == 0){
			int * arr;
			int n = argc - 2;
			int i = 0;
			arr = malloc(n*sizeof(int));
			for(;i<n;i++){				
  			        sscanf(argv[i+2], "%d", &arr[i]);
			}
			mergesort(arr, n, sizeof(int), cmp_int);
			for(i = 0;i<n;i++){
            			printf("%i ", arr[i]);
			}
		}
		if(compare_str("char", argv[1]) == 0){
			char * arr;
			int n = argc - 2;
			int i = 0;
			arr = malloc(n*sizeof(char));
			for(i=0;i<n;i++){
            			sscanf(argv[i+2], "%c", &arr[i]);
			}
			mergesort(arr, n, sizeof(char), compare_int);
			for(i=0;i<n-2;i++){
            			printf("%c", arr[i]);
			}
		if(strcmp(argv[1],"str")==0){
			size_t n=argc-2;
			char *arr[n];
			size_t i;
			for(i=2;i<n+2;i++){
				arr[i-2]=argv[i];
			}
			mergesort (arr, n,sizeof(char*), cmp_str);
			for(i=0;i<n;i++){
				printf("%s",arr[i]);
			}

		}
        }
}
return 0;
}


