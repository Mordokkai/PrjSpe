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
char s[255];
while(i<nbLig){
    fscanf(f,"%d %d %d %d",&(mi->coeffs)[4*i+3],&(mi->coeffs)[4*i+2],&(mi->coeffs)[4*i+1],&(mi->coeffs)[4*i+0],&s);
    i++;
}
}

Vr_entree_fichier(Vr* vr, int nbLig, FILE* f){

}
VI_entree_fichier(VI* vi, int nbLig, FILE* f){

}
Mr_entree_fichier(Mr* mr, int nbCol, int nbLig, FILE* f){

}


void afficher_MI(MI* mi){
    printf("Les dimensions du MI sont: %d %d",mi->dim1,mi->dim2);
    int i=0;
    for(i=0;i<mi->dim2;i++){
    printf("%d %d %d %d \n", *(mi->coeffs++),*(mi->coeffs++),*(mi->coeffs++),*(mi->coeffs++));
    }
}



