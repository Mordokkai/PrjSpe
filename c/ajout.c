//#include "ajout.h"

/* LES STRUCTURES

*/

#include <stdlib.h>
#include <stdio.h>

typedef struct {
	int x;
	int y;
} Pixel;

typedef struct {

} MI;

typedef struct {

} Vr;

typedef struct {
	int num;
} VI;

typedef struct {

} Mr;


int v(VI* vi, unsigned int s){return 0;}
int vn(VI* vi){return 0;}
int m(MI* m,int x, int y){return 0;}
void Vr_affiche(int i, Vr* vr, char* s){}
















int getNbStages() {
	//printf("jbfibfeksbfke");
	FILE* f = fopen("haarcascade_frontalface_short.txt","r");
	int c;
int nb=0;
	if(f==NULL) {
		printf("Problème lors de l'ouverture du fichier");
	}
	else{
		
		do{
			c = fgetc(f);
			if(c=='S') {nb++; 
			printf("%d",nb);}
			//printf("coucou");
		}
		while(c!=EOF);
	}
	return nb;
	fclose(f);

}

int main(int argc, char *argv[]) {
printf("coucouuuu");
	printf("Nombre de stages: %d",getNbStages());

}












