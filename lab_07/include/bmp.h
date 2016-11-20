#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
struct file_header {
char magic[2];
int32_t file_size;
int16_t reserved[2];
int32_t offset;
}__attribute__((packed));

struct info_header {
	int32_t header_size;
	int32_t width;
	int32_t height;
	int16_t bits_per_pixel;
	int32_t compression;
	int32_t bitmap_data_size;
	int32_t hor_pixels_per_meter;
	int32_t vert_pixels_per_meter;
	int32_t number_of_colors;
	int32_t number_of_important_colors;
}__attribute__((packed));

typedef struct {
uint8_t blue;
uint8_t green;
uint8_t red;
} rgb;
struct bmp_file{
struct file_header fheader;
struct info_header iheader;
rgb** picture;
}__attribute__((packed));

void load_bmp(char *filename, struct bmp_file *rpic);
void crop(struct bmp_file *pict, struct bmp_file *new_pict, int w, int h, int x, int y);
void rotate(struct bmp_file* pict, struct bmp_file *new_pict);
void save_bmp(char *filename, struct bmp_file *pict);

