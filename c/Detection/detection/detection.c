#include <stdlib.h>
#include <stdio.h>
#include "detection.h"
#include "ajout.h"
#include "vecteurs.h"
#include "../../../image_integrale/image_integrale.h"



/* MACROS*/
#define v(a,b) a[b]
#define m(a,i,j) a[i][j]
#define vn(a) a.dim

int main(int argc, char *argv[]) {
	char* file="haarcascade_frontalface_short.txt";
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
	fclose(doc);

}







