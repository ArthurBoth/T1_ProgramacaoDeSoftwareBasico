#include <stdio.h>
#include "lib_ppm.h"

int main(void)
{
	struct image_s data;
	struct image_s *image = &data;
	struct image_s data2;
	struct image_s *newImage = &data2;
	int i, j, r, s;
	
	r = read_ppm("lena.ppm", image);
	
	s = new_ppm(newImage, (image->width * 3), (image->height * 3));
	
	if (r == 0 && s == 0) {
		for (j = 0; j < image->height; j++) {
			for (i = 0; i < image->width; i++) {
				image->pix[j * newImage->width + i].r = 255;
				image->pix[j * newImage->width + i].g = 255;
				image->pix[j * newImage->width + i].b = 255;
			}
		}
		
		write_ppm("test.ppm", image);
		free_ppm(image);
	}
	
	
	return 0;
}
