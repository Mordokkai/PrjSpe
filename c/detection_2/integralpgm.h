#ifndef INTEGRALPGM_H_INCLUDED
#define INTEGRALPGM_H_INCLUDED
#include"pgm.h"

typedef struct integralPgm{
    pgmFormat* pgm;
    uint16_t width;
    uint16_t height;
    int32_t** values;
}integralPgm;

integralPgm generateIntegralPgm(pgmFormat pgm);
integralPgm generateIntegralPgm_sq(pgmFormat pgm);

void printIntegralPgm(integralPgm integral);
void saveIntegralPgm(integralPgm pgm, char* filename);
void scalePgm(pgmFormat* pgm);




#endif // INTEGRALPGM_H_INCLUDED
