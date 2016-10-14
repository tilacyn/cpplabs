#include <stdlib.h>
#include "position.h"
#include "clist.h"
#include <stddef.h>
#include <string.h>
#include <stdio.h>


void print_node(intrusive_node *node,void* fmt) {
	char* format= fmt;
	position_node *pnode = get_position(node);
	printf(format, pnode -> x, pnode -> y);
	printf("\n");
}


void count_node(intrusive_node *node,void* x) {
    	int* z = x;
    	*z = *z + 1;
}



void apply(intrusive_list *l, void (*operation)(intrusive_node*, void*), void* x){
    	intrusive_node *head = &l -> head;
    	intrusive_node *node = head -> next;
    	for (; node != head -> prev; node = node -> next){
	operation(node, x);
	}
}


int main(int argc, char* argv[]){
intrusive_list list;
intrusive_list* l = &list;
init_list(l);

if(strcmp(argv[1],"loadtext") == 0){
	FILE *file = fopen(argv[2], "r");
	while(!feof(file)){
		int x, y;
		fscanf(file, "%d %d", &x, &y);		
        	add_position(l, x, y);		
		}
	fclose(file);
	}


if(strcmp(argv[1], "loadbin") == 0){
	FILE *file = fopen(argv[2], "rb");	
	while(!feof(file)){
		char arr[6];
		int x = 0, y = 0;
		fread(arr, sizeof(char), 6, file);
		char* x_pos = (char*)&x;
		char* y_pos = (char*)&y;
		*(x_pos) = arr[0];
		*(y_pos) = arr[3];
		*(x_pos + 1) = arr[1];
		*(y_pos + 1) = arr[4];
		*(x_pos + 2) = arr[2];
		*(y_pos + 2) = arr[5];
		add_position(l, x, y);
		}
	fclose(file);
	}

int i = 3;
for(; i < argc; i++){
if(strcmp(argv[i], "savetext") == 0){
	FILE *out_file = fopen(argv[i+1], "w");	
	intrusive_node *head = &l->head;
        intrusive_node *node = head->next;
        for (; node != head->prev; node = node->next) {
        	position_node *pnode = get_position(node);
        	fprintf(out_file, "%d %d\n", pnode->x, pnode->y);
        }
	fclose(out_file);
	i++;
	}


if(strcmp(argv[i], "savebin") == 0){
	FILE *out_file = fopen(argv[i+1], "w");
	intrusive_node* head = &l -> head;
        intrusive_node* node = head -> next;
        for (; node != head -> prev; node = node -> next) {
        	position_node *pnode = get_position(node);
        	int* point_x = &(pnode -> x);
		int* point_y = &(pnode -> y);
		char* c_point_x = (char*)point_x;
		char* c_point_y = (char*)point_y;
    fwrite(c_point_x + 1, sizeof(char), 3, out_file);
		fwrite(c_point_y + 1, sizeof(char), 3, out_file);
	}
	fclose(out_file);
	i++;
	}
	

if(strcmp(argv[i], "print") == 0){
	char* fmt = argv[++i];
	apply(l, &print_node, fmt);
	}
}


if(strcmp(argv[i], "count") == 0){
	int p = 0;
	apply(l, &count_node, &p);
	printf("%d\n", p);
	}


remove_all(l);
}
