#include <stdio.h>
#include "lib_ppm.h"

int main(void)
{
	struct image_s data;
	struct image_s *image = &data;
	int i, j, r;
	
	r = read_ppm("lena.ppm", image);
	
	r = new_ppm(image, (image->width * 3), (image->height * 3));
	
	if (r == 0) {
		for (j = 0; j < image->height; j++) {
			for (i = 0; i < image->width; i++) {
				image->pix[j * image->width + i].r = 255;
				image->pix[j * image->width + i].g = 255;
				image->pix[j * image->width + i].b = 255;
			}
		}
		
		write_ppm("test.ppm", image);
		free_ppm(image);
	}
	
	
	return 0;
}
