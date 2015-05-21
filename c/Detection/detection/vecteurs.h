#ifndef VECTEURS__H
#define VECTEURS__H
#include <stdio.h>
#include <stdlib.h>
struct Vr{
	int dim;
	float* coeffs;
};

typedef struct Vr Vr;

struct VI{
	int dim;
	int* coeffs;
};

typedef struct VI VI;

struct MI{
    int dim1;
    int dim2;
	int* coeffs;
};

typedef struct MI MI;


struct Mr{
    int dim1;
    int dim2;
    float* coeffs;
};

typedef struct Mr Mr;

typedef struct {
	int x;
	int y;
} Pixel;

typedef struct Haar_Cascade {
  Pixel d;
  float area, inv_area; //area c'est l'aire supérieure gauche du pixel
  MI *rect;
  Vr *weight;
  VI *feature_rect;
  Mr *feature_threshold;
  VI *stage_feature;
  Vr *stage_threshold;

} Haar_Cascade;

MI* MI_alloue_special(int useless, int dim1, int dim2);
Vr* Vr_alloue_special(int useless, int dim) ;
VI* VI_alloue_special(int useless, int dim);
Mr* Mr_alloue_special(int useless, int dim1, int dim2);



MI_entree_fichier(MI* mi, int nbCol, int nbLig, FILE* f);
Vr_entree_fichier(Vr* vr, int nbLig, FILE* f);
VI_entree_fichier(VI* vi, int nbLig, FILE* f);
Mr_entree_fichier(Mr* mr, int nbCol, int nbLig, FILE* f);

#endif
