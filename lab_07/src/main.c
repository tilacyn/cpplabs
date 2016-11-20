#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../include/bmp.h"

int main(int argc, char* argv[]){
	struct bmp_file *pict;
	pict = malloc(sizeof(struct bmp_file));
	struct bmp_file *new_pict;
	new_pict = malloc(sizeof(struct bmp_file));	
	struct bmp_file *so_new_pict;
	so_new_pict = malloc(sizeof(struct bmp_file));	
	char* f1 = argv[2];
	char* f2 = argv[3];
	int x = atoi(argv[4]);
	int y = atoi(argv[5]);
	int w = atoi(argv[6]);
	int h = atoi(argv[7]);
	load_bmp(f1, pict);
	int32_t width = pict->iheader.width;
	int32_t height = abs(pict->iheader.height);
	if(x + w > width){
		return 0;
	}
	if(y + h > height){
		return 0;
	}
	if(x >= width){
		return 0;
	}
	if(y >= height){
		return 0;
	}
	crop(pict, new_pict, x, y, w, h);
	rotate(new_pict, so_new_pict);
	save_bmp(f2, so_new_pict);
	return 0;
}

