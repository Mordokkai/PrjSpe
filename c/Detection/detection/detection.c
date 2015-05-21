#include <stdlib.h>
#include <stdio.h>
#include "detection.h"
#include "ajout.h"
#include "vecteurs.h"
#include "../../image_integrale/image_integrale.h"



/* MACROS*/
#define v(a,b) a[b]
#define m(a,i,j) a[i][j]
#define vn(a) a.dim

int main(int argc, char *argv[]) {
	/*char* file="haarcascade_frontalface_short.txt";
	FILE* doc = fopen(file, "r");
	printf("\nNombre de stages: %d",getNbStages(doc));
	printf("\nNombre de features de S=1: %d", getNbFeatures(0,doc));
	printf("\nLe seuil pour S=1: %.16f", getSeuil(0,doc));
	Feature* feature = getFeature(3, 1, doc);
	printf("\nLe feature 3 pour S=1: %.16f, %.16f, %.16f", feature->seuil, feature->lvalue, feature->rvalue);
	Rect* r=getRectangle(2, 3, 2, doc);
	printf("\nLe rectangle 2 pour F=3 et S=2: %d, %d, %d, %d, %d", r->xi, r->yi, r->tx,r->ty,r->weight);
	Rect* r1=getRectangle(1, 3, 2, doc);

	printf("\nLe rectangle 1 pour F=3 et S=2: %d, %d, %d, %d, %d", r1->xi, r1->yi, r1->tx,r1->ty,r1->weight);
	fclose(doc);*/

	char* fichier="haar_s8.list";
    FILE* file = fopen(fichier, "r");
	int rect_n, feat_n, s_n; //nombre total de rectangle, feature, stage
  char tmp[256];
  int i;
    Haar_Cascade* c = malloc(sizeof(Haar_Cascade));

    Haar_Cascade_read_list(c,file);




/*
  fscanf(file, "%s %d %d", tmp, &c->d.x, &c->d.y); //taille zone
  fscanf(file, "%s %d", tmp, &rect_n);
  fscanf(file, "%s %d", tmp, &feat_n);
  fscanf(file, "%s %d", tmp, &s_n);

	//Init ?
  c->rect= MI_alloue_special(1, 4, rect_n);
  c->weight= Vr_alloue_special(1, rect_n);
  c->feature_rect= VI_alloue_special(1, feat_n);
  c->feature_threshold= Mr_alloue_special(1, 3, feat_n);
  c->stage_feature= VI_alloue_special(1, s_n);
  c->stage_threshold= Vr_alloue_special(1, s_n);

  c->area=1.0*(c->d.x-2)*(c->d.y-2); //Calcul de l'aire supérieure gauche du pixel
  c->inv_area=1.0/c->area;

	//Construction ?
  MI_entree_fichier(c->rect, 4, rect_n, file);			//Construction rectangle ? 4 pour le nombre de trucs à lire ?
Vr_entree_fichier(c->weight, rect_n, file);				//Creation poids
  VI_entree_fichier(c->feature_rect, feat_n, file);	//Creation feature
  Mr_entree_fichier(c->feature_threshold, 3, feat_n, file);	//3 éléments à lire, seuil, left_value, rightvalue
  VI_entree_fichier(c->stage_feature, s_n, file);
  Vr_entree_fichier(c->stage_threshold, s_n, file);




afficher_MI(c->rect);
afficher_Vr(c->weight);
afficher_VI(c->feature_rect);
afficher_Mr(c->feature_threshold);
afficher_VI(c->stage_feature);
afficher_Vr(c->stage_threshold);*/
fclose(file);

}







