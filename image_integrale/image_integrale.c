#include "pixmap_io.h"
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
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
			*(ii+j*width+i) = *(img+j*width+i) + *(ii+(j-1)*width+i) + *(ii+j*width+i-1) + *(ii+(j-1)*width+i-1);//ii(i,j) = i(i,j) + ii(i, j-1) + ii(i-1, j) - ii(i-1, j-1);
		}
	}

	return ii;
}

main(int argc, char** argv){
	unsigned char* image;
	int width, height, lumin;
    int i, j;
    int tab= 0;

    image = load_pixmap("../img/feep.pgm",&width,&height,&lumin);
    printf("%c \n \n \n",image[5]);
	for (i=0; i < width*height; i++){
		printf("%d  ", atoi(image+i));
		if(tab == width -1)
		{
			printf("\n");
			tab = 0;
		}	
		tab++;
		
	}
    /*for (j = 0; j < height; j++) {
		for (i = 0; i < width; i++) {
                printf("%d ",(unsigned char) atoi(image+j*width+i));
		}
		printf("\n");
	}
    int32_t* int_image = integral_image(image, width, height);*/
    /*for (j = 0; j < height; j++) {
		for (i = 0; i < width; i++) {
                printf("%d ",*(int_image+j*width+i));
		}
		printf("\n");
	}*/
	
	/*
	unsigned char* data;
	int width, height,lumin;

	if( (argc>1) && ((data = load_pixmap(argv[1],&width,&height,&lumin)) != NULL))
		store_pixmap("clone.pgm",data,width,lumin,height);
	*/

	return 0;
}


