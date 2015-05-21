#ifndef VECTEURS__H
#define VECTEURS__H
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
    int* coeffs;
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

VI VI_alloue_special(int dim, int what);
Vr Vr_alloue_special(int dim, int what);
void Vr_desalloue(Vr* vr);
void affiche_Vr(Vr vr);
void affiche_VI(VI vi);
#endif
