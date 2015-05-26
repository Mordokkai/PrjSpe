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


void Haar_Cascade_read_list(Haar_Cascade *c, FILE *file);
void Haar_normalize_rects(Haar_Cascade *c);
void Vr_affiche(int i, Vr* vr , char* s);

MI* construit_Image_Integrale(char* nom_img);
MI* construit_Image_Integrale_Carre(char* nom_img);
int img_int_rect_eval(MI *m, int x , int y, int tx, int ty);
int Haar_evaluate(Haar_Cascade *c, MI *img_int, MI* img_sq_int, Pixel o);
void  termine_programme(void);
void message_erreur(void);
void colorer_Pixel(MI* mi, Pixel p, Haar_Cascade c);
void out_visage(char* nom_img_in, Pixel* p, int nb_Cadres, Haar_Cascade c);

#endif
