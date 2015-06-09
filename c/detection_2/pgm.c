#include"pgm.h"
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<pthread.h>

pgmFormat* readPgm (FILE *f){

    pgmFormat* pgm = malloc(sizeof(pgmFormat));
    if(pgm==NULL)
    {
        printf("Allocation error");
        return NULL;
    }
    char c;
    short counter = 0;

parse:
    if(counter>2)
        goto data;
    c=fgetc(f);
    while(c=='\n' || c =='\t' || c==' ')
        c=fgetc(f);
    if(c=='#')
        while(c!='\n')
            c=fgetc(f);
    else{
        switch(counter){
            case 0:
                if(c!='P'){
                    printf("This is not a pgm file");
                     return NULL;
                }

                pgm->magicNumber[0]=c;
                pgm->magicNumber[1]=fgetc(f);
                break;
            case 1:
                //width and height
                fseek(f, -1, SEEK_CUR);

                if(fscanf(f,"%u %u", &pgm->width, &pgm->height)!=2)
                {
                    printf("Incomplete file");
                    return NULL;
                }
                break;
            case 2:
                //max_val
                fseek(f, -1, SEEK_CUR);
                if(fscanf(f,"%u", &pgm->maxValue)!=1)
                {
                    printf("Incomplete file");
                    return NULL;
                }
                break;
        }
        counter++;
    }
    goto parse;


data:
    if(fgetc(f)!='\n')
        return NULL;
    int i=0, j=0;

    uint16_t** p = (uint16_t**)malloc(pgm->height*sizeof(uint16_t*));

    for(i=0; i<pgm->height; i++)
    {
        p[i]= (uint16_t*) malloc(pgm->width*sizeof(uint16_t));
        for(j=0; j<pgm->width; j++)
        {
            if(feof(f))
            {
                printf("Incomplet file\n");
                return NULL;
            }
            else{
                fscanf(f,"%u", &p[i][j]);
                if(p[i][j]<0)
                    printf("All values must be positve");            }
        }
    }
    pgm->values = p;
    return pgm;
}


void printPgm(pgmFormat pgm)
{
    printf("***PGM***\n");
    printf("width=%u height=%u\n", pgm.width, pgm.height);
    printf("maxVal=%u\n", pgm.maxValue);
    printf("Data:\n");

        for(int i=0; i<pgm.height; i++)
        {
            for(int j=0; j<pgm.width; j++)
                printf("%3d ", pgm.values[i][j]);
            printf("\n");
        }
}

#include<string.h>

void savePgm (pgmFormat pgm, char* filename){
    //printing the histogram
    printf("Saving file...\n");
    FILE* f= fopen(filename, "w+");
    if(f==NULL)
    {
        printf("Error saving the file");
        return;
    }
    fprintf(f, "%c%c\n%u %u\n%u\n", pgm.magicNumber[0], pgm.magicNumber[1],pgm.width, pgm.height, pgm.maxValue);
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

void linearNormalization(pgmFormat* pgm){
    // Linear Normalization of the pgm format
    // the formula used can be found on wikepedia
    // this is used to have a maxValue equal to 255
    uint16_t max = pgm->maxValue;
    uint16_t newMax = 255;
    for(int i = 0; i<pgm->height; i++){
        for(int j = 0; j< pgm->width; j++)
        {
            pgm->values[i][j]= (uint16_t)ceil(pgm->values[i][j]*newMax/max);
        }
    }
}

void histogramEqualization(pgmFormat* pgm){
    //this allows to have an image with mean 0 and unit variance
    //the pgm struct pointed by the function's param must be normliszed
    uint32_t numberOfPixels = pgm->width*pgm->height;
    double prob[255];

    //initialization
    for(int i = 0; i<256; i++)
        prob[i]=0;

    //filing prob[255]
    for(int i=0; i<pgm->height; i++)
        for(int j=0; j<pgm->width; j++)
            prob[pgm->values[i][j]]++;
    for(int i = 0; i<256; i++)
        prob[i]/=numberOfPixels;

    //nomilizing
    uint16_t fij;
    for(int i=0; i<pgm->height; i++ )
    {
        for(int j; j<pgm->width; j++)
        {
            fij=pgm->values[i][j];
            pgm->values[i][j]=0;
            for (int k=0; k<=fij; k++)
            {
                pgm->values[i][j]+=prob[k];
            }
            pgm->values[i][j]=floor(255*pgm->values[i][j]);
        }
    }

}


