#ifndef AJOUT__H
#define AJOUT__H



typedef struct {
	float seuil;
	float lvalue;
	float rvalue;
} Feature;

typedef struct {
	int xi;
	int yi;
	int tx;
	int ty;
	int weight;
} Rect;


int getNbStages();
void initPlacement(FILE* f);
int getNbFeatures(int s, FILE * f);
float getSeuil(int n_s, FILE * f);
Feature* getFeature(int nb_f, int n_s, FILE * f);
Rect* getRectangle(int nb_r, int nb_f, int n_s, FILE * f);
#endif
