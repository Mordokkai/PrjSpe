#include"pgm.h"
#include"integralpgm.h"
#include<inttypes.h>
#include<stdlib.h>
#include<stdio.h>
integralPgm generateIntegralPgm(pgmFormat pgm){
    integralPgm integral;
    integral.pgm=&pgm;
    integral.height=pgm.height;
    integral.width=pgm.width;

    //initiliazition

    integral.values=(int32_t **)malloc(integral.height*sizeof(int32_t*));

    for(int i=0; i<integral.height; i++)
    {
        integral.values[i]=malloc(integral.width*sizeof(int32_t));
        for(int j = 0; j<integral.width; j++)
        {
            integral.values[i][j]=-1;
        }
    }

    uint32_t calculate(int32_t i, int32_t j)
    {
        if(integral.values[i][j]!=-1)
            return integral.values[i][j];
        if(i==0 && j==0)
            return pgm.values[i][j];
        if(i==0 && j!=0)
            return integral.values[i][j-1]+pgm.values[i][j];
        if (j==0 && i!=0)
            return integral.values[i-1][j]+pgm.values[i][j];

        return pgm.values[i][j]+calculate(i-1,j)+calculate(i,j-1)-calculate(i-1,j-1);


    }

    for(int i=0; i<integral.height; i++)
    {
        for(int j = 0; j<integral.width; j++)
        {
            integral.values[i][j]=calculate(i,j);
        }
    }
    return integral;


}


integralPgm generateIntegralPgm_sq(pgmFormat pgm){
    integralPgm integral;
    integral.pgm=&pgm;
    integral.height=pgm.height;
    integral.width=pgm.width;

    //initiliazition

    integral.values=(int32_t **)malloc(integral.height*sizeof(int32_t*));

    for(int i=0; i<integral.height; i++)
    {
        integral.values[i]=malloc(integral.width*sizeof(int32_t));
        for(int j = 0; j<integral.width; j++)
        {
            integral.values[i][j]=-1;
        }
    }

    uint32_t calculate(int32_t i, int32_t j)
    {
        if(integral.values[i][j]!=-1)
            return integral.values[i][j];
        if(i==0 && j==0)
            return pgm.values[i][j]*pgm.values[i][j];
        if(i==0 && j!=0)
            return integral.values[i][j-1]+pgm.values[i][j]*pgm.values[i][j];
        if (j==0 && i!=0)
            return integral.values[i-1][j]+pgm.values[i][j]*pgm.values[i][j];

        return pgm.values[i][j]*pgm.values[i][j]+calculate(i-1,j)+calculate(i,j-1)-calculate(i-1,j-1);


    }

    for(int i=0; i<integral.height; i++)
    {
        for(int j = 0; j<integral.width; j++)
        {
            integral.values[i][j]=calculate(i,j);
        }
    }
    return integral;


}

#define PRINTING_WIDTH "%6d "

void printIntegralPgm(integralPgm integral){
    printf("***INGRAL-PGM***\n");
    printf("width=%u height=%u\n", integral.width, integral.height);
    printf("Data:\n");

        for(uint16_t i=0; i<integral.height; i++)
        {
            for(uint16_t j=0; j<integral.width; j++)
                printf(PRINTING_WIDTH, integral.values[i][j]);
            printf("\n");
        }
}

void saveIntegralPgm(integralPgm pgm, char* filename){
    //printing the histogram
    printf("Saving file...\n");
    FILE* f= fopen(filename, "w+");
    if(f==NULL)
    {
        printf("Error saving the file");
        return;
    }
//    fprintf(f, "%c%c\n%u %u\n%u\n", pgm.magicNumber[0], pgm.magicNumber[1],pgm.width, pgm.height, pgm.maxValue);
    fflush(f);
    printf("Printing Data...\n");
    for(int i =0; i<pgm.height; i++)
        {
            for(int j =0; j<pgm.width; j++)
            {
                fprintf(f,"%d\n",pgm.values[i][j]);
            }
            //fprintf(f,"\n");
            fflush(f);
        }
    fclose(f);
    printf("%s has been saved\n", filename);

}
