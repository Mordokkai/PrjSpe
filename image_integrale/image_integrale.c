#include "pixmap_io.h"
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
// x >
// y V
// *(data+j*width+i)
int32_t* integral_image(unsigned char* img, int width, int height) {
	int32_t* ii = calloc(width*height, sizeof(int32_t));
	int i,j;

	// Ligne 0
	*ii = *img; //ii(0,0) = img(0,0);	// Première case
	for (i = 1; i < width; i++) {
        *(ii+i) = *(img+i) + *(ii+i-1);//ii(i,0) = i(i,0) + ii(i-1, 0);
	}

	// Lignes restantes
	for (j = 1; j < height; j++) {
		*(ii+j*width) = *(img+j*width) + *(ii+(j-1)*width);//ii(0,j) = i(0,j) + ii(0, j-1);	// Première colonne
		for (i = 1; i < width; i++) {
			*(ii+j*width+i) = *(img+j*width+i) + *(ii+(j-1)*width+i) + *(ii+j*width+i-1) - *(ii+(j-1)*width+i-1);//ii(i,j) = i(i,j) + ii(i, j-1) + ii(i-1, j) - ii(i-1, j-1);
		}
	}

	return ii;
}

int32_t* int_img(char* fichier, int* width, int* height, int* lumin){
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
	
	return integral_image(image, *width, *height);
}

main(int argc, char** argv){
	int width, height, lumin;
	if(argc!=2) {
		printf("Utilisation :\n./image_integrale \"fichier.pgm\"\n");
		exit(1);
	}
	int32_t* int_image = int_img(argv[1], &width, &height, &lumin);
	
	// Affichage de image
    /*for (j = 0; j < height; j++) {
		for (i = 0; i < width; i++) {
                printf("%d\t",*(image+j*width+i));
		}
		printf("\n");
	}*/
    
    // Affichage de l'image intégrale
    int i, j;
    for (j = 0; j < height; j++) {
		for (i = 0; i < width; i++) {
                printf("%d\t",*(int_image+j*width+i));
		}
		printf("\n");
	}
	
	// Clonage d'une image
	/*unsigned char* data;
	int width, height,lumin;

	if( (argc>1) && ((data = load_pixmap(argv[1],&width,&height,&lumin)) != NULL))
		store_pixmap("clone.pgm",data,width,lumin,height);*/

	return 0;
}


