#include "vecteurs.h"

/**ALLOCATIONS**/


MI* MI_alloue_special(int useless, int dim1, int dim2){
	MI* mi = (MI*) malloc(sizeof(VI));
	mi->dim1=dim1;
	mi->dim2=dim2;
	mi->coeffs=(int *) malloc(dim1*dim2*sizeof(int));
	return mi;
}

Vr* Vr_alloue_special(int useless, int dim) {
	Vr* vr = (Vr*) malloc(sizeof(Vr));
	vr->dim=dim;
	vr->coeffs=(float *) malloc(dim*sizeof(float));
	return vr;
}

VI* VI_alloue_special(int useless, int dim){
	VI* vi = (VI*) malloc(sizeof(VI));
	vi->dim=dim;
	vi->coeffs=(int *) malloc(dim*sizeof(int));
	return vi;
}


Mr* Mr_alloue_special(int useless, int dim1, int dim2){
	Mr* mr = (Mr*) malloc(sizeof(Mr));
	mr->dim1=dim1;
	mr->dim2=dim2;
	mr->coeffs=(int *) malloc(dim1*dim2*sizeof(int));
	return mr;
}

void Vr_desalloue(Vr* vr){
	free(vr->coeffs);
	free(vr);
}


void affiche_Vr(Vr vr){
	int i;
  printf("[ ");
  for(i = 0; i < vr.dim; i++) {
    printf("%f ", vr.coeffs[i]);
  }
  printf("]");
}

/**AFFICHAGE**/
void affiche_VI(VI vi){
	int i;
  printf("[ ");
  for(i = 0; i < vi.dim; i++) {
    printf("%d ", vi.coeffs[i]);
  }
  printf("]");
}

/**CONSTRUCTION**/
MI_entree_fichier(MI* mi, int nbCol, int nbLig, FILE* f){
int i=0;
while(i<nbLig*nbCol){
    fscanf(f,"%d ",&(mi->coeffs)[i]);
    i++;
}
}

Vr_entree_fichier(Vr* vr, int nbLig, FILE* f){
int i=0;
while(i<nbLig){
    fscanf(f,"%f",&(vr->coeffs)[i]);
    i++;
}
}
VI_entree_fichier(VI* vi, int nbLig, FILE* f){
int i=0;
while(i<nbLig){
    fscanf(f,"%d",&(vi->coeffs)[i]);
    i++;
}
}
Mr_entree_fichier(Mr* mr, int nbCol, int nbLig, FILE* f){
int i=0;
while(i<nbLig*nbCol){
    fscanf(f,"%f ",&(mr->coeffs)[i]);
    //printf("youpi");
    i++;
}
}


void afficher_MI(MI* mi){
    printf("Les dimensions du MI sont: %d %d",mi->dim1,mi->dim2);
    int i=0;
    for(i=0;i<mi->dim2;i++){
    printf("%d %d %d %d \n", *(mi->coeffs++),*(mi->coeffs++),*(mi->coeffs++),*(mi->coeffs++));
    }
}

void afficher_Mr(Mr* mr){
    printf("Les dimensions du Mr sont: %d %d",mr->dim1,mr->dim2);
    int i=0;
    for(i=0;i<mr->dim2;i++){
        int j=0;
        for(j=0;j<mr->dim1;j++){
            printf("%f ", *(mr->coeffs++));
        }
        printf("\n");
    }
}

void afficher_Vr(Vr* vr){
    printf("La dimension du Vr est: %d",vr->dim);
    int i=0;
    for(i=0;i<vr->dim;i++){
    printf("%f\n", *(vr->coeffs++));
    }
}
void afficher_VI(VI* vi){
    printf("La dimension du VI est: %d",vi->dim);
    int i=0;
    for(i=0;i<vi->dim;i++){
    printf("%d\n", *(vi->coeffs++));
    }
}

