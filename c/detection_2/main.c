#include <stdio.h>
#include <stdlib.h>

#include"pgm.h"
#include"integralpgm.h"
#include"classiefier.h"
int main(int argc, char ** argv)
{
    pgmFormat* pgm;
    printf("Hello world!\n");
    puts(argv[1]);
    FILE* f = fopen(argv[1],"r");
    if(f==NULL)
        printf("***error***\n");
    else
        printf("***Reading***\n");
        pgm=readPgm(f);
        if(pgm == NULL)
            printf("not a pgm file");
    //printPgm(*pgm);



////    fclose(f);
    printf("\n****\nCASCADE****\n");
    Cascade* cascade = openCascade("../../cascade/haarcascade_frontalface_short.txt");
    printf("\n*****\SCANING*****\n");
    scanPgm(cascade,pgm);



    return 0;
}
