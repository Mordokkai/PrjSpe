#include "../image_integrale/pixmap_io.h"
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include "../image_integrale/image_io.h"

void Resample(char* fichier, int newWidth, int newHeight)
    {
    	int width,height,lumin;
    	int cy = 0;
    	int cx = 0;
    	int pixel;
    	int i = 0;
    	int j = 0;
    	int nearestMatch;
		unsigned char* data = lire_image(fichier,&width,&height,&lumin);
        unsigned char* newData = (unsigned char *)malloc(newWidth * newHeight);

        double scaleWidth =  (double)newWidth / (double)width;
        double scaleHeight = (double)newHeight / (double)height;

        for(cy = 0; cy < newHeight; cy++)
        {
            for(cx = 0; cx < newWidth; cx++)
            {
                pixel = (cy * (newWidth)) + (cx);
                nearestMatch =  (((int)(cy / scaleHeight) * (width)) + ((int)(cx / scaleWidth)) );

                newData[pixel    ] =  data[nearestMatch    ];
                newData[pixel + 1] =  data[nearestMatch + 1];
                newData[pixel + 2] =  data[nearestMatch + 2];
            }
        }
        FILE* fichierOut = fopen("group_scaled_final.pgm","w");
        //on ecrit d'abord l'entete
        fprintf(fichierOut,"%s\n%d %d\n%d\n","P2",newWidth,newHeight,lumin);
        for(i=0;i < newWidth * newHeight;i++)
	{
			fprintf(fichierOut,"%d ",newData[i]);
			j++;
			if (j == newWidth - 1)
				fprintf(fichierOut,"\n");
	}
        fclose(fichierOut);
        //delete[] _data;
        //_data = newData;
        //_width = newWidth;
        //_height = newHeight;
}

int* scaling(int* data, int width, int height, int newWidth, int newHeight) {
    if(width==newWidth) {printf("on y passe") ;return data;}
	long long int cy = 0;
	long long int cx = 0;
	long long int pixel;
	long long int i = 0;
	long long int j = 0;
	long long int nearestMatch;
    //int* newData = (int *)malloc(newWidth * newHeight*sizeof(int));
    int newData[1024*1024];
    double scaleWidth =  (double)newWidth / (double)width;
    double scaleHeight = (double)newHeight / (double)height;

    for(cy = 0; cy < newHeight; cy++)
    {
        for(cx = 0; cx < newWidth; cx++)
        {
            pixel = (cy * (newWidth)) + (cx);
            nearestMatch =  (((int)floor((cy / scaleHeight))* (width)) + ((int)floor((cx / scaleWidth))) );

            newData[pixel] =  data[nearestMatch    ];
            newData[pixel + 1] =  data[nearestMatch + 1];
            //if(nearestMatch+2>width * height ||pixel+2>width * height )
            //printf("fuck");
            newData[pixel + 2] =  data[nearestMatch+2];

        }
    }



    return newData;

}
    /*
main()
{
	//int width;
	//int height;
	//int lumin;
	int newWidth = 256;
	int newHeight = 256;

	Resample("../../img/barbara.pgm",newWidth,newHeight);

}*/



/*
unsigned char* lire_entree_IM(FILE* f, int *width, int *height, int *lumin){
    char tmp[10];
    fscanf(f,"%s %d %d %d",tmp, width,height,lumin);
    int i=0;
    unsigned char* mi=calloc((*width)*(*height),sizeof(unsigned char));
    unsigned char* q=mi;
    for(i=0;i<(*width)*(*height);i++){
        fscanf(f,"%d",(unsigned int*)q);
        q++;
    }
    return mi;
}

main()
{
	int width, height, lumin, cpt=1;
	char fichier_out[10];
	unsigned char * redim;

	printf("Debut Lecture\n");
	//unsigned char * image = lire_image("../../img/lena.ascii.pgm",&width,&height,&lumin);
	FILE* fichier_in = fopen("../../img/lena.ascii.pgm","r");
	unsigned char * image = (unsigned char *)lire_entree_IM(fichier_in,&width,&height,&lumin);
	fclose(fichier_in);
	ecrire_image("clone.pgm", image, width, height, lumin);
	int newWidth = width;
	int newHeight = height;

	while(newWidth > 24 && newHeight > 24) {
		printf("Boucle %d\n", cpt);
		newWidth = newWidth/1.25;
		newHeight = newHeight/1.25;
		redim = scaling(image, width, height, newWidth, newHeight);
		sprintf(fichier_out, "img%d.pgm", cpt);
		ecrire_image(fichier_out, redim, newWidth, newHeight, lumin);
		cpt++;
		free(redim);
	}

}
*/

