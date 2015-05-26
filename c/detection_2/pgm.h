#ifndef PGM_H_INCLUDED
#define PGM_H_INCLUDED
#include<stdint.h>
#include<stdio.h>

typedef struct pgmFormat
{
    char magicNumber[2];
    uint16_t width;
    uint16_t height;
    uint16_t maxValue;
    uint16_t** values;
}pgmFormat;

/**
*  @param f: a pgm file
*  @return null if f isn't a pgm format.
*/
pgmFormat* readPgm (FILE *f);

/**
*   save the pgm structure to a pgm_file
*   @param pgm: pgm structure
*
*/
void savePgm (pgmFormat pgm, char* filename);
void linearNormalization(pgmFormat* pgm);
//void sigmoidNormalization(pgmFormat* pgm, int alpha, int beta);
void histogramEqualization(pgmFormat* pgm);
void printPgm(pgmFormat pgm);



#endif // PGM_H_INCLUDED
