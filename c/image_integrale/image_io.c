#include "pixmap_io.h"
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>

unsigned char* lire_image(char* fichier, int* width, int* height, int* lumin) {
	unsigned char* data;
	unsigned char buffer[3];
    int i, j;
    
	if( (data = load_pixmap(fichier,width,height,lumin)) == NULL) {
		printf("Erreur à la lecture de l'image");
		exit(1);
	}
	unsigned char* image = calloc((*width)*(*height), sizeof(unsigned char));
	buffer[0] = '0';
	buffer[1] = '0';
	buffer[2] = '0';
    int cpt = 0, cpt2 = 0;
	for (i=0; i < strlen(data); i++){
		if(*(data+i)==32 || *(data+i)==10) {
			if (cpt2==1) {
				image[cpt] = (unsigned char) atoi(buffer);
				buffer[2] = '0';
				cpt++;
				cpt2=0;
			}
			if (cpt2==2) {
				unsigned char tmp = buffer[2];
				buffer[2] = buffer[1];
				buffer[1] = tmp;
				image[cpt] = (unsigned char) atoi(buffer);
				buffer[1] = '0';
				buffer[2] = '0';
				cpt++;
				cpt2=0;
			}
			if (cpt2==3) {
				unsigned char tmp = buffer[2];
				buffer[2] = buffer[0];
				buffer[0] = tmp;
				image[cpt] = (unsigned char) atoi(buffer);
				buffer[0] = '0';
				buffer[1] = '0';
				buffer[2] = '0';
				cpt++;
				cpt2=0;
			}
		} else {
			buffer[2-cpt2] = *(data+i);
			cpt2++;
		}
	}
	return image;
}

void ecrire_image(char* fichier, unsigned char* image, int width, int height, int lumin) {
	int i=0;
	unsigned char* data;
	unsigned char buffer[5];
	int cpt = 0, cpt2 = 0, cpt3 = 0;
	data = calloc(width * height * 4, sizeof(unsigned char));
	for (i = 0; i < width * height; i++){
		if(cpt2>66 || cpt3 >= width){
			cpt2=0;
			cpt3=0;
			sprintf(data+cpt, "\n");
			cpt++;
		}
		sprintf(buffer, "%d ", *(image+i));
		*(data+cpt) = buffer[0];
		cpt++;
		cpt2++;
		*(data+cpt) = buffer[1];
		cpt++;
		cpt2++;
		if(*(image+i) > 9) {
			*(data+cpt) = buffer[2];
			cpt++;
			cpt2++;
		}
		if(*(image+i) > 99) {
			*(data+cpt) = buffer[3];
			cpt++;
			cpt2++;
		}
		cpt3++;
	}
	store_pixmap(fichier,data,width,lumin,height);
	free(data);
}
