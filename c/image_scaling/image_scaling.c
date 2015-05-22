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
    	int nearestMatch;
		unsigned char* data = lire_image(fichier,&width,&height,&lumin);
        unsigned char* newData = (unsigned char *)malloc(newWidth * newHeight * 3);

        double scaleWidth =  (double)newWidth / (double)width;
        double scaleHeight = (double)newHeight / (double)height;

        for(cy = 0; cy < newHeight; cy++)
        {
            for(cx = 0; cx < newWidth; cx++)
            {
                pixel = (cy * (newWidth *3)) + (cx*3);
                nearestMatch =  (((int)(cy / scaleHeight) * (width *3)) + ((int)(cx / scaleWidth) *3) );
                
                newData[pixel    ] =  data[nearestMatch    ];
                newData[pixel + 1] =  data[nearestMatch + 1];
                newData[pixel + 2] =  data[nearestMatch + 2];
            }
        }
        FILE* fichierOut = fopen("group_scaled.pgm","w");
        //on ecrit d'abord l'entete
        fprintf(fichierOut,"%s\n%d %d\n%d\n","P2",newWidth,newHeight,lumin);
        for(i=0;i < newWidth * newHeight * 3;i++)
	{
		fprintf(fichierOut,"%d\n",newData[i]);
	}
        fclose(fichierOut);
        //delete[] _data;
        //_data = newData;
        //_width = newWidth;
        //_height = newHeight;
    }
    
main()
{
	//int width;
	//int height;
	//int lumin;
	int newWidth = 80;
	int newHeight = 60;
	
	Resample("../../img/groupe1_160x120a.pgm",newWidth,newHeight);
	
}
	
