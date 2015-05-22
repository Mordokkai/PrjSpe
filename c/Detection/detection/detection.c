#include <stdlib.h>
#include <stdio.h>
#include "detection.h"
#include "ajout.h"
#include "vecteurs.h"
#include "../../image_integrale/image_integrale.h"
#include <math.h>


/* MACROS*/


#define min(X, Y) (((X) < (Y)) ? (X) : (Y))
#define v(a,i) a->coeffs[i]
#define m(a,i,j) a->coeffs[i*a->dim2+j]
#define mn0(a) a->dim1
#define mn1(a) a->dim2
#define vn(a) a->dim

int main(int argc, char **argv) {
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
/*
	char* fichier="haar_s8.list";
    FILE* file = fopen(fichier, "r");
	int rect_n, feat_n, s_n; //nombre total de rectangle, feature, stage
  char tmp[256];
  int i;
    Haar_Cascade* c = malloc(sizeof(Haar_Cascade));

    Haar_Cascade_read_list(c,file);
    MI* mi=construit_Image_Integrale("../../../img/feep.pgm");
    //afficher_MI(mi);
    printf("Valeur deduite: %d",img_int_rect_eval(mi,0,0,24,7));
*/
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










  char nomimg[255];
//  Image *image;
  MI *m;
  MI *r;
  Mr *tr;
  FILE *trf;	//Pointeur vers le fichier contenant les seuils

  //parametre_verbose=sortie=sortie_verbose=erreur=stdout;
  float SEUIL_ZERO=1e-6;
  if (argc==1)
    {
      printf("usage : obj_detect_Haar  Haar_cascade.list img \n");
      exit(0);
    }
  /* Des bricoles d'initialisation */
  //Texte_initialise(5);

  printf("Go!");
    printf("%s",argv[2]);
  strcpy(nomimg,argv[2]);

  FILE *f_c=fopen(argv[1], "r");
    if(f_c==NULL){printf("Ne trouve pas le classifier");}
	//On crée la structure de cascade à partir du fichier texte
  Haar_Cascade c;
  Haar_Cascade_read_list(&c, f_c);
  fclose(f_c);
  printf("Haar OK!\n");


/**FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF**/


//On va créer l'image intégrale
  //MI8u *m8u;	//????????????
  int i,j;
  /* lit l'image d'entrée */
//MI* mi=construit_Image_Integrale(nomimg);
  //m8u=MI8u_lit_image(NULL, nomimg);

  printf("Img OK!\n");fflush(stdout);
  //MI8u_visualise(m8u, 1 , "&", "img");

  /**FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF**/


  /* convertit en 32 bits */
  //m=MI_alloue_special(1, mn0(m8u),  mn1(m8u));
  //toMxx(m, m8u);

  //M3I *mipmapiso;
  //MI_taille triso;
  float scale=0.83;
  int filter_threshold=12;
  int filter_size=6;

  int  scale_level=-log(min(mn0(m)/(c.d.x+2), mn1(m)/(c.d.y+2)))/log(scale)+1;

  int level=-scale_level*log(scale)/log(2)+2;

  printf("scale_level=%d level=%d\n", scale_level, level);

  //mipmapiso=M3I_alloue_special(1, mn0(m), mn1(m), level);
  /* Construit la mipmap qui  servira pour tous les niveaux d'échelle */
  //mipmap_gen_iso_MI(mipmapiso, triso,  m, level);
  //M3I_visualise(mipmapiso, 1 , "&", "mipmapiso");
  /* Allocations diverses */
  MI *scaled, *scaled_int, *scaled_sq, *scaled_sq_int, *mt;
  //MI *detect;
  //MI8u  *detect_filled;
  //M3I8u *detect_binary,*detect_binary_filtered,*detect_binary_filled;
  //VI *cpt_y;

  //scaled=MI_alloue_special(1, mn0(mipmapiso),  mn1(mipmapiso));
  //MI* scaled= mi;

  //scaled_int=MI_alloue_special(1, mn0(mipmapiso),  mn1(mipmapiso));
  //scaled_sq=MI_alloue_special(1, mn0(mipmapiso),  mn1(mipmapiso));
  //scaled_sq_int=MI_alloue_special(1, mn0(mipmapiso),  mn1(mipmapiso));
  //mt=MI_alloue_special(1, mn0(mipmapiso),  mn1(mipmapiso));
  //detect=MI_alloue_special(1, mn0(mipmapiso),  mn1(mipmapiso));
  //detect_filled=MI8u_alloue_special(1, mn0(mipmapiso),  mn1(mipmapiso));

  //detect_binary=M3I8u_alloue_special(1, mn0(mipmapiso),  mn1(mipmapiso), scale_level);
  //detect_binary_filtered=M3I8u_alloue_special(1, mn0(mipmapiso),  mn1(mipmapiso), scale_level);
  //detect_binary_filled=M3I8u_alloue_special(1, mn0(mipmapiso),  mn1(mipmapiso), scale_level);
  //cpt_y=VI_alloue_special(1, mn0(mipmapiso));

  //M3I8u_zero(detect_binary);
  //M3I8u_zero(detect_binary_filtered);
  //M3I8u_zero(detect_binary_filled);
  //VI_zero(cpt_y);
  //MI_cst(detect, 128);
  //float sc;
  //int s;

  //sc=1.0;

  //M3I8u *pyr;
  //pyr=M3I8u_alloue_special(1,  m3n0(detect_binary),  m3n1(detect_binary),  scale_level);
  //M3I8u_zero(pyr);
  //M4I *intcarre;
  //intcarre=M4I_alloue_special(1,  m3n0(detect_binary),  m3n1(detect_binary),  m3n2(detect_binary), 2);
  //M4I_zero(intcarre);
/*???????????????????????*/




  /* Parcours tous les niveaux d'échelle */
  //printf("Echelle\n");
 // for(s=0;s<scale_level;s++)
    //{
      //printf("s=%d\n",s);
      /* Construit  chaque niveau à partir de la mipmap */
     // scale_from_mipmap_iso_img_MI(scaled, mipmapiso , triso,  sc);
      /* Calcule le carre, l'image intégrale et l'image intégrale du carre */

      scaled_int=construit_Image_Integrale(nomimg);
      scaled_sq_int=construit_Image_Integrale_Carre(nomimg);
      afficher_MI(scaled_int);
      afficher_MI(scaled_sq_int);
      //MI_carre(scaled_sq, scaled);
      //img_integral_MI(scaled_int, scaled);
      //img_integral_MI(scaled_sq_int, scaled_sq);
      /*for(int ii=0; ii<m4n0(intcarre);ii++)
        for(int jj=0; jj<m4n1(intcarre);jj++)
          {
            m3(pyr, ii, jj, s)=m(scaled, ii, jj);
            m4(intcarre, ii, jj, s, 0)=m(scaled_int, ii, jj);
            m4(intcarre, ii, jj, s, 1)=m(scaled_sq_int, ii, jj);
          }*/
      //int  r;
      Pixel o;
      printf("Haar evaluate\n");
      int cpt=0;
      /* Pour tous les pixels de l'image, detecte une zone */
      for(o.y=0; o.y<mn1(scaled_int)-c.d.y;o.y++){
        for(o.x=0; o.x<mn0(scaled_int)-c.d.x;o.x++)
          {
            //    if (  (o.x+ o.y*mn0(scaled))%1000==0)
            // printf("%d %d\n", o.x, o.y);
            if (Haar_evaluate(&c, scaled_int, scaled_sq_int, o))
              {
                printf("DETECTEEEE %d %d", o.x, o.y);
                cpt++;
                //m3(detect_binary, o.x, o.y, s)=255;
                /* si trouve une zone, ajoute nbre de détections (*2)*/
                //int i,j;
                //for(i=0;i<c.d.x/sc;i++)
                  //for(j=0;j<c.d.y/sc;j++)
                    //m(detect, (int)(o.x/sc+i), (int)(o.y/sc+j))+=10;
              }
          }

          }
          printf("Il y a: %d visages détéctés.",cpt);
      //sc*=scale;
    //}
 //M3I8u_ecrit_image_P5(detect_binary, "res/detect_binary.pgm");
  //M3I8u_ecrit_image_P5(detect_binary_filtered, "res/detect_binary_filtered.pgm");
  //Mxxmul(detect_filled, detect_filled, mipmapiso);
  //MI8u_visualise(detect_filled, 1, "&", "detect_filled");
  //MI8u_ecrit_image_P5(detect_filled, "res/detect_filled.pgm");
  //M3I8u_ecrit_image_P5(pyr, "res/pyr.pgm");
  //M4I_ecrit_image_P5(intcarre, "res/intcarre.pgm");


}






