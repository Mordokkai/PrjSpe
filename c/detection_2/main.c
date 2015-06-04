#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#include"pgm.h"
#include"integralpgm.h"
#include"detector.h"

int main(int argc, char ** argv)
{
    pgmFormat* pgm;
    printf("Hello world!\n");
    for(int i=1; i<argc;i++){
        puts(argv[i]);
        FILE* f = fopen(argv[i],"r");
        if(f==NULL)
            printf("***Error***\n");
        else
            printf("***Reading***\n");

        pgm=readPgm(f);
        if(pgm == NULL)
            printf("not a pgm file");

        Cascade* cascade = openCascade("../../cascade/haarcascade_frontalface_default.txt");
        printStageList(cascadeToStageList(cascade));

        printf("\n*****\SCANING*****\n");

        char *resultName=malloc(sizeof(char)*(strlen(argv[i])+5));
        resultName = strcpy(resultName,argv[i]);
        resultName = strcat(resultName,".rs");
        scanPgm(cascade,pgm,resultName);
    }



    return 0;
}
