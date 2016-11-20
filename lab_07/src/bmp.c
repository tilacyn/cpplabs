#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/bmp.h"
/*
void load_bmp(char* filename, struct bmp_file* rpic){
FILE *f = fopen(filename, "rb");
fread(&rpic->fheader,sizeof(struct file_header),1,f);
fread(&rpic->iheader,sizeof(struct info_header),1,f);
int32_t width=rpic->iheader->width;
int32_t height=abs(rpic->iheader->height);
int32_t numbo =(4-width%4)%4;
rpic->picture=malloc(sizeof(rgb*)*height);
rgb* buf=malloc(sizeof(rgb)*4);
for(int i=height-1;i>=0;i--){
rpic->picture[i]=malloc(sizeof(rgb)*width);
fread(rpic->picture[i],sizeof(rgb),width,f);
if(numbo!=0)fread(buf,sizeof(rgb),numbo,f);
}
free(buf);
fclose(f);
}

RGBTRIPLE** crop(struct bmp_file* pic,int x,int y, int w,int h){
int32_t width=pic->iheader.width;
int32_t height=abs(pic->iheader.height);
RGBTRIPLE **croppic=malloc(sizeof(RGBTRIPLE*)*h);
for(int i=y;i<y+h&&i<height;i++){
croppic[i-y]=malloc(sizeof(RGBTRIPLE*)*w);
for(int j=x;j<x+w&&j<width;j++){
croppic[i-y][j-x]=pic->picture[i][j];
}
}
for(int i=0;i<height;i++)free(pic->picture[i]);
free(pic->picture);
return croppic;
}
RGBTRIPLE **rotate(RGBTRIPLE** pic,int w,int h){
RGBTRIPLE **rotpic=malloc(sizeof(RGBTRIPLE*)*w);
for(int i=0;i<w;i++){
rotpic[i]=malloc(sizeof(RGBTRIPLE*)*h);
for(int j=0;j<h;j++){
rotpic[i][j]=pic[h-j-1][i];
}
}
for(int i=0;i<h;i++)free(pic[i]);
free(pic);
return rotpic;
}
void savebmp(char* filename,struct bmp_file* bmp,RGBTRIPLE** pic,int w,int h){
FILE *sf = fopen(filename, "w");
bmp->iheader.height=h;
bmp->iheader.width=w;
size_t nullsize = (4-w%4)%4;
bmp->iheader.bitmap_data_size=(w+nullsize)*h*3;
fwrite(&bmp->fheader, sizeof(struct file_header), 1, sf);
fwrite(&bmp->iheader, sizeof(struct info_header),1,sf);
RGBTRIPLE tmp;
tmp.red=0;
tmp.blue=0;
tmp.green=0;
for(int i=h-1;i>=0;i--){
fwrite(pic[i],sizeof(RGBTRIPLE),w,sf);
if(nullsize)fwrite(&tmp,sizeof(RGBTRIPLE),nullsize,sf);
}
for(int i=0;i<h;i++)free(pic[i]);
free(pic);
free(bmp);
return;
}
*/
void load_bmp(char* filename, struct bmp_file* pict){
	//printf("oh, so kekushke");	
	FILE *f = fopen(filename, "rb");
	fread(&pict->fheader, sizeof(struct file_header), 1, f);
	fread(&pict->iheader, sizeof(struct info_header), 1, f);
	//printf("oh, so kekushke");	
	void* buffer = malloc(4 * sizeof(rgb));
	int32_t i = abs(pict->iheader.height) - 1;	
	pict->picture = malloc(sizeof(rgb*) * pict->iheader.height);
	for(; i > -1; i--){
		pict->picture[i] = malloc(pict->iheader.width * 3);
		fread(pict->picture[i], 3, pict->iheader.width, f);
		if((4 - (pict->iheader.width % 4)) % 4)
			fread(buffer, 3, (4 - (pict->iheader.width % 4)) % 4, f);
	}
	fclose(f);
	free(buffer);
}

void crop(struct bmp_file* pict, struct bmp_file* new_pict, int x, int y, int w, int h){
	int i = 0;
	memcpy(&new_pict->fheader, &pict->fheader, sizeof(struct file_header));
	memcpy(&new_pict->iheader, &pict->iheader, sizeof(struct info_header));
	new_pict->iheader.width = w;
	new_pict->iheader.height = h;
	new_pict->picture = malloc(sizeof(rgb*) * h);
	for(; i < h; i++){
		new_pict->picture[i] = malloc(w * 3);
		memcpy(new_pict->picture[i], pict->picture[i + y] + x, w * 3);
	}
	for(int k = 0; k < h; k++){
		free(pict->picture[k]);		
	}
	free(pict->picture);
	free(pict);
}

void rotate(struct bmp_file* pict, struct bmp_file* new_pict){
	int i = 0;
	memcpy(&new_pict->fheader, &pict->fheader, sizeof(struct file_header));
	memcpy(&new_pict->iheader, &pict->iheader, sizeof(struct info_header));
	int32_t h = pict->iheader.height;
	int32_t w = pict->iheader.width;
	new_pict->iheader.width = h;
	new_pict->iheader.height = w;
	new_pict->picture = malloc(sizeof(rgb*) * w);	
	int k = 0;	
	for(; k < w; k++){
		new_pict->picture[k] = malloc(sizeof(rgb) * h);
	}
	for(; i < h; i++){
		int j = 0;
		for(; j < w; j++){
			new_pict->picture[j][h - i - 1].green = pict->picture[i][j].green;
			new_pict->picture[j][h - i - 1].blue = pict->picture[i][j].blue;
			new_pict->picture[j][h - i - 1].red = pict->picture[i][j].red;
		}
	}

	for(k = 0; k < h; k++){
		free(pict->picture[k]);		
	}
	free(pict->picture);
	free(pict);
}
void save_bmp(char* filename, struct bmp_file* pict){
	FILE *f = fopen(filename, "w");
	int null_length = (4 - (pict->iheader.width % 4)) % 4;
	pict->iheader.bitmap_data_size = (pict->iheader.width + null_length) * pict->iheader.height * 3;
	fwrite(&pict->fheader, sizeof(struct file_header), 1, f);
	fwrite(&pict->iheader, sizeof(struct info_header), 1, f);
	int i = 0;
	rgb null_pix;
	printf("%d %d %d", pict->iheader.bitmap_data_size, pict->iheader.width, pict->iheader.height);
	null_pix.blue = 0;
	null_pix.green = 0;
	null_pix.red = 0;
	for(i = pict->iheader.height - 1; i > -1; i--){
		fwrite(pict->picture[i], 3, pict->iheader.width, f);
		int k = 0;
		for(; k < null_length; k++){
			fwrite(&null_pix, 3, 1, f);
		}
		free(pict->picture[i]);
	}
	free(pict->picture);
	free(pict);
	fclose(f);
}



