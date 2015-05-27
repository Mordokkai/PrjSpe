#ifndef CLASSIEFIER_H_INCLUDED
#define CLASSIEFIER_H_INCLUDED

#include<stdint.h>
#include<stdbool.h>
#include<stdio.h>
#include"integralpgm.h"

typedef struct Window{
    uint16_t width;
    uint16_t height;
}Window;

typedef struct Detector{
    Window window;
    uint16_t x;
    uint16_t y;
}Detector;

typedef struct Cascade{
    FILE* file;
    Window D;
}Cascade;

typedef struct Rectangle{
    uint16_t x;
    uint16_t y;
    uint16_t w;
    uint16_t h;
    long double weight;

}Rectangle;

typedef struct Feature
{
    int type;
    Rectangle* rect;//depends on the feature type
    long double f; //seuil
    long double gt;
    long double ls;
}Feature;

#include<stdbool.h>

typedef struct Stage
{
    long double threshold; // seuil de stage
    uint16_t numberOfFeatures;
    Feature* features;
    bool last; // true if it's the last stage;
}Stage;


Cascade* openCascade(char* filename);
Stage loadNextStage(Cascade* cascade);
bool scaleFeature(Feature* f, Cascade* cascade, uint16_t coef, integralPgm integral);


long double stageEvaluation(Stage stage, Detector detector, integralPgm* ii);
long double rectangleEvaluation(Rectangle r, Detector d, integralPgm* ii);
long double FeatureEvalution(Feature f, Detector d, integralPgm* ii);

bool hasPassedStage(Stage stage, Detector detector, integralPgm* ii);
void printStage( Stage stage);






#endif // CLASSIEFIER_H_INCLUDED
