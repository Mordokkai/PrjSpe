#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include "ajout.h"

//int v(VI* vi, unsigned int s){return 0;}
//int vn(VI* vi){return 0;}
//int m(MI* m,int x, int y){return 0;}
//void Vr_affiche(int i, Vr* vr, char* s){}

int getNbStages(FILE* f) {
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
		}
		while(c!=EOF);
	}
	return nb;

}


void initPlacement(FILE* f){
	fseek(f, 0, SEEK_SET);
	int tmp;
	do{
		tmp=fgetc(f);
	}
	while(tmp!='D');
}



//Le premier stage est le numero 0
int getNbFeatures(int s, FILE*f) {
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

}

//Un float est codé sur 32 bits
float getSeuil(int n_s, FILE* f) {

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
	return resultat;
	}
}


Feature* getFeature(int nb_f, int n_s, FILE* f){
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
	}
}



Rect* getRectangle(int nb_r, int nb_f, int n_s, FILE *f){
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
			}

		}
		while(n_s!=nb && c!=EOF);

		//On se positionne au bon feature-1
		int num_f=0;
		do{
			c = fgetc(f);
			if(c=='F') {num_f++;
			}

		}
		while(num_f<= nb_f-1 && c!=EOF);
		//On se positionne au bon rectangle
		char *tmp;
		int i=0;
		while(i<nb_r){
			do{c=fgetc(f); } while(c!='R' && c!=EOF);
			fscanf(f, "%d %d %d %d %d",&(rect->xi),&(rect->yi),&(rect->tx),&(rect->ty),&(rect->weight));
			i++;
		}

		return rect;
	}



}














