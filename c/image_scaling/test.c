#include "../image_integrale/pixmap_io.h"
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include "../image_integrale/image_io.h"

main()
{
	int width;
	int height;
	int i = 0; 
	int lumin;
	unsigned char* image = lire_image("../../img/groupe1_160x120a.pgm",&width,&height,&lumin);
	for(i=0;i<10;i++)
		printf("%d \n",image[i]);
}
	
