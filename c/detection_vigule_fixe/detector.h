#ifndef DETECTOR_H_INCLUDED
#define DETECTOR_H_INCLUDED

#include<inttypes.h>


typedef struct{
    FILE* file;
    uint16_t width;
    uint16_t height;
}Cascade;

typedef struct Rectangle{
    uint16_t x;
    uint16_t y;
    uint16_t w;
    uint16_t h;
    double weight;

}Rectangle;

typedef struct Feature
{
    int type;
    Rectangle* rect;//depends on the feature type
    double f; //seuil
    double gt;
    double ls;
}Feature;

#include<stdbool.h>

typedef struct Stage
{
    double threshold; // seuil de stage
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

void maxThresholds (Cascade cascade, double * sth, double *fth, double* fgt, double* fls);




#endif // DETECTOR_H_INCLUDED
