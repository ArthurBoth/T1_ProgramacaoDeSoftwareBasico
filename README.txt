27/04/2033 - Arthur Both e Gustavo Melo
Dos arquivos fornecidos, o Makefile foi alterado (para códigos de terminal de windows), e a imagem (antes lena.ppm) 
foi alterada para "image.ppm".

O código se baseia na utilização de duas estruturas de dados de imagem, uma para a imagem a ter o seu tamanho 
aumentado e outra para a versão da imagem como tamanho já aumentado.

Para as comparações, foram utilizadas simples argumentos de 'if-else-if', levando sempre em conta que uma comparação 
é mais eficiente que duas ('x<75' é mais eficiente que 'x>0 && x<75'), bem como verificar se o valor de algo é maior 
que 0 ou menor que 255 é redundate, visto que valores RGB, naturalmente, estão entre (inclusivo) 0 e 255.

Ademais, neste documento de texto adicionarei uma cópia do código comentado linha-a-linha por razões de completude.



#include <stdio.h>
#include "lib_ppm.h"

int main(void)
{
	struct image_s og; // "objeto" de imagem da imagem original
	struct image_s *ogImage = &og; // ponteiro para o endereço do "objeto" original
	struct image_s new; // "objeto" de imagem da nova imagem
	struct image_s *newImage = &new; // ponteiro para o endereço do "objeto" da nova imagem
	int i, j, r, s; // 'i' e 'j' são variáveis de iteração, 'r' e 's' são utilizados para a verificação de erros
	int h1, w1, h2, w2; // 'h1' e 'w1' são a altura e largura da imagem original e 'h2' e 'w2' são a altura e largura da nova imagem respectivamente
	int red, green, blue; // variáveis que armazenarão as cores dos pixeis da imagem original

	r = read_ppm("image.ppm", ogImage); // verifica o tamanho da imagem original
	w1 = ogImage->width; // guarda a largura da imagem original
	h1 = ogImage->height; // guarda a altura da imagem original
	w2 = w1*3; // triplica a largura da imagem original
	h2 = h1*3; // triplica a altura da imagem original
	s = new_ppm(newImage, w2, h2); // gera uma nova identidade de imagem com o triplo do tamanho
	
	printf("Original Image Width: %d Original Image Height: %d\n",w1,h1); // printa o tamanho da imagem original
	printf("New Image Width: %d New Image Height: %d\n",w2,h2); // printa o tamanho da nova imagem (com área 9 vezes maior)

	if (r == 0 && s == 0) {	// verifica se a leitura da imagem original e a criação da nova imagem deram certo	
		// printf("As imagens deram certo\n"); // debug flag
		for (j = 0; j < ogImage->height; j++) { // percorre a imagem original linha por linha, de cima para baixo
			for (i = 0; i < ogImage->width; i++) { // percorre a linha pixel por pixel, da esquerda para a direita
				// salva os valores RGB do pixel atual em três variáveis distintas
				red = ogImage->pix[j * ogImage->width + i].r; // red é para o valor vermelho
				green = ogImage->pix[j * ogImage->width + i].g; // green é para o valor verde
				blue = ogImage->pix[j * ogImage->width + i].b; // blue é para o valor azul
				
				// pinta os sub-pixeis vermelhos de acordo com o valor RED do pixel original
				if (red < 75){ // "Para níveis de cor de 0 a 74, todos os sub-pixels devem ser pretos;"
					newImage->pix[(j*3) * newImage->width + (i*3)].r = 0; // pixel de cima
					newImage->pix[(j*3+1) * newImage->width + (i*3)].r = 0; // pixel do meio
					newImage->pix[(j*3+2) * newImage->width + (i*3)].r = 0; // pixel de baixo
				} else if (red < 135){ //"Para níveis de cor de 75 a 134, o sub-pixel do meio deve ser da cor respectiva e os outros dois devem ser pretos;"
					newImage->pix[(j*3) * newImage->width + (i*3)].r = 0; // pixel de cima
					newImage->pix[(j*3+1) * newImage->width + (i*3)].r = 255; // pixel do meio
					newImage->pix[(j*3+2) * newImage->width + (i*3)].r = 0; // pixel de baixo
				} else if (red < 180) { // "Para níveis de cor de 135 a 179, o sub-pixel do meio deve ser preto eos outros dois devem ser da cor respectiva;"
					newImage->pix[(j*3) * newImage->width + (i*3)].r = 255; // pixel de cima
					newImage->pix[(j*3+1) * newImage->width + (i*3)].r = 0; // pixel do meio
					newImage->pix[(j*3+2) * newImage->width + (i*3)].r = 255; // pixel de baixo
				} else { // "E para níveis de cor de 180 a 255, todos os sub-pixels devem ser de sua cor respectiva."
					newImage->pix[(j*3) * newImage->width + (i*3)].r = 255; // pixel de cima
					newImage->pix[(j*3+1) * newImage->width + (i*3)].r = 255; // pixel do meio
					newImage->pix[(j*3+2) * newImage->width + (i*3)].r = 255; // pixel de baixo
				}
				
				// pinta os sub-pixeis verdes de acordo com o valor GREEN do pixel original
				if (green < 75){ // "Para níveis de cor de 0 a 74, todos os sub-pixels devem ser pretos;"
					newImage->pix[(j*3) * newImage->width + (i*3+1)].g = 0; // pixel de cima
					newImage->pix[(j*3+1) * newImage->width + (i*3+1)].g = 0; // pixel do meio
					newImage->pix[(j*3+2) * newImage->width + (i*3+1)].g = 0; // pixel de baixo
				} else if (green < 135){ //"Para níveis de cor de 75 a 134, o sub-pixel do meio deve ser da cor respectiva e os outros dois devem ser pretos;"
					newImage->pix[(j*3) * newImage->width + (i*3+1)].g = 0; // pixel de cima
					newImage->pix[(j*3+1) * newImage->width + (i*3+1)].g = 255; // pixel do meio
					newImage->pix[(j*3+2) * newImage->width + (i*3+1)].g = 0; // pixel de baixo
				} else if (green < 180) { // "Para níveis de cor de 135 a 179, o sub-pixel do meio deve ser preto eos outros dois devem ser da cor respectiva;"
					newImage->pix[(j*3) * newImage->width + (i*3+1)].g = 255; // pixel de cima
					newImage->pix[(j*3+1) * newImage->width + (i*3+1)].g = 0; // pixel do meio
					newImage->pix[(j*3+2) * newImage->width + (i*3+1)].g = 255; // pixel de baixo
				} else { // "E para níveis de cor de 180 a 255, todos os sub-pixels devem ser de sua cor respectiva."
					newImage->pix[(j*3) * newImage->width + (i*3+1)].g = 255; // pixel de cima
					newImage->pix[(j*3+1) * newImage->width + (i*3+1)].g = 255; // pixel do meio
					newImage->pix[(j*3+2) * newImage->width + (i*3+1)].g = 255; // pixel de baixo
					
				}
				
				// pinta os sub-pixeis azuis de acordo com o valor BLUE do pixel original
				if (blue < 75){ // "Para níveis de cor de 0 a 74, todos os sub-pixels devem ser pretos;"
					newImage->pix[(j*3) * newImage->width + (i*3+2)].b = 0; // pixel de cima
					newImage->pix[(j*3+1) * newImage->width + (i*3+2)].b = 0; // pixel do meio
					newImage->pix[(j*3+2) * newImage->width + (i*3+2)].b = 0; // pixel de baixo
				} else if (blue < 135){ //"Para níveis de cor de 75 a 134, o sub-pixel do meio deve ser da cor respectiva e os outros dois devem ser pretos;"
					newImage->pix[(j*3) * newImage->width + (i*3+2)].b = 0; // pixel de cima
					newImage->pix[(j*3+1) * newImage->width + (i*3+2)].b = 255; // pixel do meio
					newImage->pix[(j*3+2) * newImage->width + (i*3+2)].b = 0; // pixel de baixo
				} else if (blue < 180) { // "Para níveis de cor de 135 a 179, o sub-pixel do meio deve ser preto eos outros dois devem ser da cor respectiva;"
					newImage->pix[(j*3) * newImage->width + (i*3+2)].b = 255; // pixel de cima
					newImage->pix[(j*3+1) * newImage->width + (i*3+2)].b = 0; // pixel do meio
					newImage->pix[(j*3+2) * newImage->width + (i*3+2)].b = 255; // pixel de baixo
				} else { // "E para níveis de cor de 180 a 255, todos os sub-pixels devem ser de sua cor respectiva."
					newImage->pix[(j*3) * newImage->width + (i*3+2)].b = 255; // pixel de cima
					newImage->pix[(j*3+1) * newImage->width + (i*3+2)].b = 255; // pixel do meio
					newImage->pix[(j*3+2) * newImage->width + (i*3+2)].b = 255; // pixel de baixo
				}
						
			}
		}
		
		
		write_ppm("new_image.ppm", newImage);
		free_ppm(newImage);
	}
	
	free_ppm(ogImage);
	return 0;
}