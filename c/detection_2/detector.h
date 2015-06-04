#ifndef DETECTOR_H_INCLUDED
#define DETECTOR_H_INCLUDED

#include"integralpgm.h"
#include"pgm.h"
#include<stdint.h>

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

typedef struct lstage
{
    Stage element;
    struct lstage* next;
}* StageList;


Cascade* openCascade(char* filename);
Stage loadNextStage(Cascade* cascade);
StageList addStageList(StageList l, Stage e);
StageList cascadeToStageList(Cascade *cascade);
void printStage( Stage stage);
StageList cascadeToStageList(Cascade *cascade);
void printStageList(StageList l);

long double stageEvaluation(Stage stage, Detector detector, integralPgm* ii, integralPgm* ii_sq);
long double rectangleEvaluation(Rectangle r, Detector d, integralPgm* ii);
long double FeatureEvalution(Feature f, Detector d, integralPgm* ii, integralPgm* ii_sq);
bool hasPassedStage(Stage stage, Detector detector, integralPgm* ii, integralPgm* ii_sq);

void scanPgm(Cascade* cascade, pgmFormat *i, char* resultName);
void printDetector(Detector d, pgmFormat* pgm);





#endif // DETECTOR_H_INCLUDED
