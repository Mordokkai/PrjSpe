//#include "ajout.h"

/* LES STRUCTURES

*/

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

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



int v(VI* vi, unsigned int s){return 0;}
int vn(VI* vi){return 0;}
int m(MI* m,int x, int y){return 0;}
void Vr_affiche(int i, Vr* vr, char* s){}
















int getNbStages(char* doc) {
	//printf("jbfibfeksbfke");
	FILE* f = fopen(doc,"r");
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


void initPlacement(FILE* f){
	int tmp;
	do{
		tmp=fgetc(f);
	}
	while(tmp!='D');
}



//Le premier stage est le numero 0
int getNbFeatures(int s, char* doc) {
	FILE* f = fopen(doc,"r");
	initPlacement(f);
	int c;
	int nb=0;
	int nb_f=0;
	if(f==NULL) {
		printf("Problème lors de l'ouverture du fichier");
	}
	else{
		//On se positionne au bon stage
		do{
			c = fgetc(f);
			if(c=='S') {nb++; 
			}
			//printf("coucou");
		}
		while(nb!=s && c!=EOF);

		//On compte le nombre de feature
		do{
			c=fgetc(f);
			if(c=='F') {nb_f++;}
		}
		while(c!='S' && c!=EOF);
	}
	
	return nb_f;
	fclose(f);

}

//Un float est codé sur 32 bits
float getSeuil(int n_s, char* doc) {
	
	FILE* f = fopen(doc,"r");
	initPlacement(f);
	int c;
	int nb=-1;
	float resultat;
	if(f==NULL) {
		printf("Problème lors de l'ouverture du fichier");
	}
	else{
		//On se positionne au bon stage
		do{
			c = fgetc(f);
			if(c=='S') {nb++; 
			}
			//printf("coucou");
		}
		while(n_s!=nb && c!=EOF);
		fscanf(f, "%f",&resultat);
		//printf("Recupéré en poubelle: %d", tmp);
	return resultat;
	fclose(f);
	}
}


Feature* getFeature(int nb_f, int n_s, char* doc){
	FILE* f = fopen(doc,"r");
	initPlacement(f);
	int c;
	int nb=0;
	float resultat;
	Feature* feature= malloc(sizeof(Feature));
	if(f==NULL) {
		printf("Problème lors de l'ouverture du fichier");
	}
	else{
		//On se positionne au bon stage
		do{
			c = fgetc(f);
			if(c=='S') {nb++; 
			}
			//printf("coucou");
		}
		while(n_s!=nb && c!=EOF);
		
		//On se positionne au bon feature
		int num_f=0;
		do{
			c = fgetc(f);
			if(c=='F') {num_f++; 
			}
			
		}
		while(num_f!= nb_f && c!='S' && c!=EOF);

		fscanf(f,"%f %f %f", &(feature->seuil), &(feature->lvalue), &(feature->rvalue));
		return feature;
	fclose(f);
	}
}



Rect* getRectangle(int nb_r, int nb_f, int n_s, char* doc){
	FILE* f = fopen(doc,"r");
	initPlacement(f);
	int c;
	int nb=0;
	float resultat;
	Rect* rect= malloc(sizeof(Rect));
	if(f==NULL) {
		printf("Problème lors de l'ouverture du fichier");
	}
	else{
		//On se positionne au bon stage
		do{
			c = fgetc(f);
			if(c=='S') {nb++; 
printf("stageeee");
			}
			
		}
		while(n_s!=nb && c!=EOF);
		
		//On se positionne au bon feature-1
		int num_f=0;
		do{
			c = fgetc(f);
			if(c=='F') {num_f++; 
			printf("featureeee");
			}
			
		}
		while(num_f<= nb_f-1 && c!=EOF);
		//On se positionne au bon rectangle
		char *tmp;
		int i=0;
		while(i<nb_r){
			do{c=fgetc(f);} while(c!='R' && c!=EOF);
			char* s;
			fgets(s,10,f);
			printf("AAAAAAAAAA %s",s);
			fscanf(f, "%d %d %d %d %d %d",&c, &(rect->xi),&(rect->yi),&(rect->tx),&(rect->ty),&(rect->weight));
			printf("Le rectangle 2 pour F=3 et S=3: %d, %d, %d, %d, %d", rect->xi, rect->yi, rect->tx,rect->ty,rect->weight);
			printf("on y est");
			i++;
		}
		
		return rect;
	fclose(f);
	}



}




int main(int argc, char *argv[]) {
	char* doc="haarcascade_frontalface_short.txt";
	printf("Nombre de stages: %d",getNbStages(doc));
	printf("Nombre de features de S=1: %d", getNbFeatures(0,doc));
	printf("Le seuil pour S=1: %.16f", getSeuil(0,doc));
	Feature* feature = getFeature(3, 1, doc);
	printf("Le feature 3 pour S=1: %.16f, %.16f, %.16f", feature->seuil, feature->lvalue, feature->rvalue);
	Rect* r=getRectangle(2, 3, 3, doc);
	printf("Le rectangle 2 pour F=3 et S=3: %d, %d, %d, %d, %d", r->xi, r->yi, r->tx,r->ty,r->weight);
}












