#include "../image_integrale/pixmap_io.h"
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include "../image_integrale/image_io.h"
#include "../Detection/detection/vecteurs.h"

void Resample(FILE* fichier, int newWidth, int newHeight)
    {
    	int width,height,lumin;
    	int cy = 0;
    	int cx = 0;
    	int pixel;
    	int i = 0;
    	int j = 0;
    	int nearestMatch;
		//unsigned char* data = lire_image(fichier,&width,&height,&lumin);
        //unsigned char* newData = (unsigned char *)malloc(newWidth * newHeight);
        MI* mi=lire_entree_IM(fichier);
        width=mi->dim1;
        height=mi->dim2;
        lumin=255;//il faudrait changer la structure
        int* data=mi->coeffs;
        //printf("jsbfdskfysdkufgksudygfkusdygfusgyd");
       // printf("%d",(mi->coeffs)[0]);
        //while(1);
        //int* newData = (int *)calloc(newWidth * newHeight,sizeof(int));
        MI* newDataMi= MI_alloue_special(1,newWidth,newHeight);
        int* newData=newDataMi->coeffs;
        double scaleWidth =  (double)newWidth / (double)width;
        double scaleHeight = (double)newHeight / (double)height;

        for(cy = 0; cy < newHeight; cy++)
        {
            for(cx = 0; cx < newWidth; cx++)
            {
                pixel = (cy * (newWidth)) + (cx);
                nearestMatch =  (((int)(cy / scaleHeight) * (width)) + ((int)(cx / scaleWidth)) );
                //printf("nearest= %d",nearestMatch);
                newData[pixel] =  data[nearestMatch];
                newData[pixel + 1] =  data[nearestMatch + 1];
                newData[pixel + 2] =  data[nearestMatch + 2];
            }
        }
        int pk=0;
        //while(pk<100000000000)pk++;
         fclose(fichier);
        FILE* fichierOut = fopen("lena.ascii.pgm","w");
        ecrire_image_pgm(newDataMi,fichierOut);
        free(data);
         MI_desalloue(newDataMi);
        //on ecrit d'abord l'entete
        //fprintf(fichierOut,"%s\n%d %d\n%d\n","P2",newWidth,newHeight,lumin);
       // for(i=0;i < newWidth * newHeight;i++)
	//{
		//	fprintf(fichierOut,"%d ",newData[i]);
			//j++;
			//if (j == newWidth - 1)
			//	fprintf(fichierOut,"\n");
	//}
        fclose(fichierOut);

        //delete[] _data;
        //_data = newData;
        //_width = newWidth;
        //_height = newHeight;*/
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

