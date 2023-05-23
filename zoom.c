#include <stdio.h>
#include "lib_ppm.h"

int main(void)
{
	struct image_s og;
	struct image_s *ogImage = &og; 
	struct image_s new;
	struct image_s *newImage = &new;
	int i, j, r, s;
	int h1, w1, h2, w2;
	int red, green, blue;

	r = read_ppm("image.ppm", ogImage);
	w1 = ogImage->width;
	h1 = ogImage->height;
	w2 = w1*3;
	h2 = h1*3;
	s = new_ppm(newImage, w2, h2);
	
	printf("Original Image Width: %d Original Image Height: %d\n",w1,h1);
	printf("New Image Width: %d New Image Height: %d\n",w2,h2);

	if (r == 0 && s == 0) {
		for (j = 0; j < ogImage->height; j++) {
			for (i = 0; i < ogImage->width; i++) {
				red = ogImage->pix[j * ogImage->width + i].r;
				green = ogImage->pix[j * ogImage->width + i].g;
				blue = ogImage->pix[j * ogImage->width + i].b;
				
				if (red < 75){
					newImage->pix[(j*3) * newImage->width + (i*3)].r = 0;
					newImage->pix[(j*3+1) * newImage->width + (i*3)].r = 0;
					newImage->pix[(j*3+2) * newImage->width + (i*3)].r = 0;
				} else if (red < 135){
					newImage->pix[(j*3) * newImage->width + (i*3)].r = 0;
					newImage->pix[(j*3+1) * newImage->width + (i*3)].r = 255;
					newImage->pix[(j*3+2) * newImage->width + (i*3)].r = 0;
				} else if (red < 180) {
					newImage->pix[(j*3) * newImage->width + (i*3)].r = 255;
					newImage->pix[(j*3+1) * newImage->width + (i*3)].r = 0;
					newImage->pix[(j*3+2) * newImage->width + (i*3)].r = 255;
				} else {
					newImage->pix[(j*3) * newImage->width + (i*3)].r = 255;
					newImage->pix[(j*3+1) * newImage->width + (i*3)].r = 255;
					newImage->pix[(j*3+2) * newImage->width + (i*3)].r = 255;
				}
				
				if (green < 75){
					newImage->pix[(j*3) * newImage->width + (i*3+1)].g = 0;
					newImage->pix[(j*3+1) * newImage->width + (i*3+1)].g = 0;
					newImage->pix[(j*3+2) * newImage->width + (i*3+1)].g = 0;
				} else if (green < 135){
					newImage->pix[(j*3) * newImage->width + (i*3+1)].g = 0;
					newImage->pix[(j*3+1) * newImage->width + (i*3+1)].g = 255;
					newImage->pix[(j*3+2) * newImage->width + (i*3+1)].g = 0;
				} else if (green < 180) {
					newImage->pix[(j*3) * newImage->width + (i*3+1)].g = 255;
					newImage->pix[(j*3+1) * newImage->width + (i*3+1)].g = 0;
					newImage->pix[(j*3+2) * newImage->width + (i*3+1)].g = 255;
				} else {
					newImage->pix[(j*3) * newImage->width + (i*3+1)].g = 255;
					newImage->pix[(j*3+1) * newImage->width + (i*3+1)].g = 255;
					newImage->pix[(j*3+2) * newImage->width + (i*3+1)].g = 255;
				}
				
				if (blue < 75){
					newImage->pix[(j*3) * newImage->width + (i*3+2)].b = 0;
					newImage->pix[(j*3+1) * newImage->width + (i*3+2)].b = 0;
					newImage->pix[(j*3+2) * newImage->width + (i*3+2)].b = 0;
				} else if (blue < 135){
					newImage->pix[(j*3) * newImage->width + (i*3+2)].b = 0;
					newImage->pix[(j*3+1) * newImage->width + (i*3+2)].b = 255;
					newImage->pix[(j*3+2) * newImage->width + (i*3+2)].b = 0;
				} else if (blue < 180) {
					newImage->pix[(j*3) * newImage->width + (i*3+2)].b = 255;
					newImage->pix[(j*3+1) * newImage->width + (i*3+2)].b = 0;
					newImage->pix[(j*3+2) * newImage->width + (i*3+2)].b = 255;
				} else {
					newImage->pix[(j*3) * newImage->width + (i*3+2)].b = 255;
					newImage->pix[(j*3+1) * newImage->width + (i*3+2)].b = 255;
					newImage->pix[(j*3+2) * newImage->width + (i*3+2)].b = 255;
				}
						
			}
		}
		write_ppm("new_image.ppm", newImage);
		free_ppm(newImage);
	}
	
	free_ppm(ogImage);
	return 0;
}