#include <stdio.h>
#include <stdlib.h>

#include"pgm.h"
#include"integralpgm.h"
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
        else
            printPgm(*pgm);

    //linearNormalization(pgm);
    //printPgm(*pgm);
    //histogramEqualization(pgm);
    //printPgm(*pgm);
    integralPgm integral = generateIntegralPgm(*pgm);
    printIntegralPgm(integral);
    fclose(f);

    return 0;
}
