#include "vecteurs.h"
#include "../../image_integrale/pixmap_io.h"
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include "../../image_integrale/image_io.h"
#include "../../image_integrale/image_integrale.h"


/**MACROS**/
#define v(a,i) a->coeffs[i]
#define m(a,i,j) a->coeffs[j*a->dim1+i]
#define mn0(a) a->dim1
#define mn1(a) a->dim2
#define vn(a) a->dim
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
void MI_desalloue(MI* mi){
	free(mi->coeffs);
	free(mi);
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
int* p=mi->coeffs;
while(i<nbLig*nbCol){
    fscanf(f,"%d ",&(p)[i]);
    i++;
}
}

Vr_entree_fichier(Vr* vr, int nbLig, FILE* f){
int i=0;
int* p=vr->coeffs;
while(i<nbLig){
    fscanf(f,"%f",&(p)[i]);
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
float* r=mr->coeffs;
while(i<nbLig*nbCol){
    fscanf(f,"%f ",&(r)[i]);
    //printf("youpi");
    i++;
}
}


void afficher_MI(MI* mi){
    printf("Les dimensions du MI sont: %d %d \n",mi->dim1,mi->dim2);
    int i=0;
    int* p=mi->coeffs;
    for(i=0;i<mi->dim2;i++){
        int j=0;
        for(j=0;j<mi->dim1;j++){
            printf("%d ", *(p++));
        }
        printf("\n");
    }
}

void ecrire_image_pgm(MI* mi,FILE* f_out){
    printf("Les dimensions du MI sont: %d %d \n",mi->dim1,mi->dim2);
    int i=0;
    //FILE*f =fopen("coucou.pgm","r+");
    fprintf(f_out,"P2\n%d %d\n255\n",mi->dim1,mi->dim2);
    int* p=mi->coeffs;
    for(i=0;i<mi->dim2;i++){
        int j=0;
        for(j=0;j<mi->dim1;j++){
            fprintf(f_out,"%d ", *(p++));
        }
        printf("\n");
    }
}

void afficher_Mr(Mr* mr){
    printf("Les dimensions du Mr sont: %d %d",mr->dim1,mr->dim2);
    int i=0;
    float* p=mr->coeffs;
    for(i=0;i<mr->dim2;i++){
        int j=0;
        for(j=0;j<mr->dim1;j++){
            printf("%f ", *(p++));
        }
        printf("\n");
    }
}

void afficher_Vr(Vr* vr){
    printf("La dimension du Vr est: %d",vr->dim);
    int i=0;
    float* p=vr->coeffs;
    for(i=0;i<vr->dim;i++){
    printf("%f\n", *(p));
    p++;
    }
}
void afficher_VI(VI* vi){
    printf("La dimension du VI est: %d",vi->dim);
    int i=0;
    int* p=vi->coeffs;
    for(i=0;i<vi->dim;i++){
    printf("%d\n", *(p++));
    }
}


MI* construit_Image_Integrale(char* nom_img){
    /**On recupère l'image intégrale**/
    int width=0, height=0, lumin=255;
    //unsigned char* image = lire_image(nom_img, &width, &height, &lumin);
    FILE* f= fopen(nom_img,"r");
    MI* image_mi=lire_entree_IM(f);
    int* image=image_mi->coeffs;
    //printf("Les params: %d %d %d",width,height,lumin);
    fclose(f);
    //printf("coucou");
	int32_t* int_image = integral_image(image, width, height);
	/**On la met dans la matrice**/
	//MI* mi= MI_alloue_special(1,width,height);
	MI* mi=calloc(1,sizeof(MI));
	mi->dim1=width;
	mi->dim2=height;
	mi->coeffs=(int *)int_image;
	free(int_image);
	MI_desalloue(image_mi);

	return mi;
}

MI* construit_Image_Integrale_Carre(char* nom_img){
    /**On recupère l'image intégrale**/
    int width=0, height=0, lumin=255;
    //unsigned char* image = lire_image(nom_img, &width, &height, &lumin);
     FILE* f= fopen(nom_img,"r");
    MI* image_mi=lire_entree_IM(f);
    int* image=image_mi->coeffs;
    //printf("Les params: %d %d %d",width,height,lumin);
    fclose(f);
	int32_t* square_int=integral_image_carre(image, width, height);
	/**On la met dans la matrice**/
	//MI* mi= MI_alloue_special(1,width,height);
	MI* mi=calloc(1,sizeof(MI));
	mi->dim1=width;
	mi->dim2=height;
	mi->coeffs=(int *)square_int;
	free(square_int);
	MI_desalloue(image_mi);

	return mi;
}


void colorer_Pixel(MI* mi, Pixel p, Haar_Cascade c){
    int i=0;

    /**La barre supérieure**/
    for(i=p.x;i<p.x+c.d.x;i++){
        m(mi,i,p.y)=250;
    }


    /**La barre de gauche**/
    i=0;
    for(i=p.y;i<p.y+c.d.y;i++){
        m(mi,p.x,i)=250;
    }
    /**La barre de droite**/

    i=0;
    for(i=p.y;i<p.y+c.d.y;i++){
        m(mi,p.x+c.d.x,i)=250;
    }
    /**La barre inférieure**/
     i=0;
    for(i=p.x;i<p.x+c.d.x;i++){//pb car p.y+c.d.y est nul selon l'image résultat
        //printf("gaedvjayztdjyatzd %d %d",i,p.y+c.d.y);
        int z=p.y+c.d.y; //Varaibale intermédiaire totalement inutile normalement mais ne marche pas sans
        m(mi,i,z)=250;
    }
}

MI* lire_entree_IM(FILE* f){
    char tmp[10];
    int width,height,lumin;
    fscanf(f,"%s %d %d %d",&tmp, &width,&height,&lumin);
    int i=0;
    MI* mi= MI_alloue_special(1,width,height);
    //int* mi=calloc(width*height,sizeof(int));
   // printf("youhou");
    int* q=mi->coeffs;
    for(i=0;i<width* height;i++){
        fscanf(f,"%d",q);
        //printf("un de plus");
        q++;
    }
    return mi;
}

void lire_entree_IM_param(FILE* f, int* width, int* height, int* lumin){
    char tmp[10];
    fscanf(f,"%s %d %d %d",&tmp, width,height,lumin);
}



void ecrire_sortie_MI(FILE* f, MI* mi){
    fprintf(f,"P2\n%d %d\n255",mi->dim1,mi->dim2);
    int i=0;
    for(i=0;i<mi->dim2*mi->dim1;i++){
        if(i%27==0) fprintf(f,"\n");
        fprintf(f,"%d ",mi->coeffs[i]);

    }

}

MI* fusion_cadre_image(MI* img, MI* cadre){
    int i=0;
    for(i=0;i<img->dim1*img->dim2;i++){
        img->coeffs[i]+=cadre->coeffs[i];
    }
    return img;
}




void out_visage(char* nom_img_in, Pixel* p, int nb_Cadres, Haar_Cascade c){
  FILE* f_in = fopen(nom_img_in,"rw");
    //FILE* f_out = fopen("sortie.pgm","wa");
    int width, height, lumin;

    //unsigned char* image = lire_image(nom_img_in, &width, &height, &lumin);
     //FILE* f= fopen(nom_img,"r");
    MI* image_mi=lire_entree_IM(f_in);
    int* image=image_mi->coeffs;
    //printf("Affichage des données lues");
    //printf("La luminosité est de %d",lumin);
    MI* mi= MI_alloue_special(1,width,height);
    //mi->coeffs=(int32_t *)image;

    int i=0;
    while(i< nb_Cadres){
        colorer_Pixel(mi,*p,c);

        printf("couleur");
        p++;
        i++;
    }
    MI* mi_img= lire_entree_IM(f_in);
    MI* mi_result=fusion_cadre_image(mi_img,mi);
    ecrire_image_pgm(mi_result,f_in);
    free(image);
    MI_desalloue(mi);
//ecrire_sortie_MI(f_out,mi);
//ecrire_image("sortie.pgm", mi->coeffs, width, height, lumin);
fclose(f_in);
//fclose(f_out);
}





















void Haar_Cascade_read_list(Haar_Cascade *c, FILE *file)
{
  int rect_n, feat_n, s_n; //nombre total de rectangle, feature, stage
  char tmp[256];
  int i;


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

/* Normalise les rectangles */
  //Haar_normalize_rects(c);


#define PREC 16
  //#define vfixe(a,prec) (trunc((a)*pow(2,prec)))/pow(2,prec)

#define vfixe(a,prec) a
//printf("HERE WE GO!!!!");
    int j,k;
    for(i=0;i<vn(c->weight);i++)
      v(c->weight, i)= vfixe(v(c->weight, i), 14);

    for(j=0;j<mn1(c->feature_threshold);j++)
      for(i=0;i<mn0(c->feature_threshold);i++)
        m(c->feature_threshold, i, j) = vfixe( m(c->feature_threshold, i, j), PREC);

    for(i=0;i<vn(c->stage_threshold);i++)
      v(c->stage_threshold, i)= vfixe(v(c->stage_threshold, i), PREC);

}


void Haar_normalize_rects(Haar_Cascade *c)
{
  unsigned int nb_rect0;
  unsigned int nb_f = 0;
  unsigned int nb_r = 0;
	//On parcourt tous les stages (Sy)
	unsigned int s=0;
  for (s = 0; s < vn(c->stage_feature); s++) {
		//On parcourt tous les haarfeatures de ce stage (Sy)
    unsigned int f=0;
    for (f = 0; f < v(c->stage_feature, s); f++) {
      nb_rect0 = nb_r;
      float sum0 = 0;
			//Parcourt des rectangles de la feature
        unsigned int r=0;
      for (r = 0; r < v(c->feature_rect, nb_f); r++) {
        //v(c->weight, nb_r) *= c->inv_area;
        if (r != 0) {
          sum0 += v(c->weight, nb_r) * 1.0*( m(c->rect, 2, nb_r) * m(c->rect, 3, nb_r));
        }
        nb_r++;
      }
      v(c->weight, nb_rect0) = -sum0 / (1.0*(m(c->rect, 2, nb_rect0) * m(c->rect, 3, nb_rect0)));
      nb_f++;
    }
  }
  //afficher_Vr(c->weight);
  //Vr_affiche(1, c->weight , "weight :");
}

/* calcul l'intégrale sur un carre de coin x, y et de largeur (tx,ty) */
int img_int_rect_eval(MI *m, int x , int y, int tx, int ty)
{
//L4-L3-L2+L1
  int r=0;
  x=x-1; y=y-1;
  int x1=x+tx, y1=y+ty;
  if (x>=0 && y>=0){
    r+= m(m, x, y);
    //printf("r vaut: %d",r);
    }
  if (x>=0){
    r-=m(m, x, y1);
    //printf("r vaut: %d",r);
    }
  if (y>=0){
    r-=m(m, x1, y);
    //printf("r vaut: %d",r);
    }
  r+=m(m, x1, y1);
  return r;
}









int Haar_evaluate(Haar_Cascade *c, MI *img_int, MI* img_sq_int, Pixel o)
{
  float mean=img_int_rect_eval(img_int, o.x+1, o.y+1, c->d.x-2, c->d.y-2);
  float sq_mean=img_int_rect_eval(img_sq_int, o.x+1, o.y+1, c->d.x-2, c->d.y-2);
  double variance_sq=sq_mean*c->area-mean*mean; // variance * c->area**2
  float variance=sqrt(variance_sq);

  //int lg=(o.x==14 && o.y==6);

  unsigned int nb_f = 0;
  unsigned int nb_r = 0;
  unsigned int nb_s = 0;
  float sum_s;
  int fail = 0;
  // Parcours des etages de la cascade
  while (nb_s < vn(c->stage_threshold) && !fail) {
    sum_s = 0;

    // Parcours des features de l'etage actuel
    unsigned int f=0;
    for (f = 0; f < v(c->stage_feature, nb_s); f++) {
      float sum_f = 0;

      // Parcours des rectangles de la feature actuelle et
      // evaluation de ces rectangles sur l'image integrale
      unsigned int r=0;
      for (r = 0; r < v(c->feature_rect, nb_f); r++) {
        int val= img_int_rect_eval(img_int,
                                   o.x+m(c->rect, 0, nb_r),
                                   o.y+m(c->rect, 1, nb_r),
                                   m(c->rect, 2, nb_r),
                                   m(c->rect, 3, nb_r)
                                   );
        //printf("ok");
        /*
          if (lg) printf("v %d %d %d %d %d\n", val, o.x+m(c->rect, 0, nb_r),
                                   o.y+m(c->rect, 1, nb_r),
                                   m(c->rect, 2, nb_r),
                                   m(c->rect, 3, nb_r));
        */
        sum_f += v(c->weight, nb_r) *val;	//Pondération
        nb_r++;
      }
      //if (lg) printf("idxf %d %f\n", f, sum_f);

      //printf("s %f\n", sum_f);
      // sum_f => sum_f * c->area car weight pas divise par c->area
      float th = m(c->feature_threshold, 0, nb_f);
      float t = th*th*variance_sq;
      //   Test les features de l'étage
      int test = (sum_f*sum_f) >= t;
      int alpha;
      //if (lg) printf("sum_f %f  %f th %f variance %f t %f\n", sum_f, sum_f*sum_f, th, variance_sq, t);
      if (sum_f>= 0 )
        {
          if (th>=0)
            alpha= test ? 1 : 0;
          else
            alpha=1;
        }
      else
        {
          if (th>0)
            alpha= 0;
          else
            alpha= (!test) ? 1 : 0;
        }
      sum_s += m(c->feature_threshold, 1+alpha, nb_f);
      //if (lg) printf("alpha : %d sum_s %f \n", alpha, sum_s);
      nb_f++;
    }
    // Test l'étage
    fail = (sum_s < v(c->stage_threshold, nb_s));
    //if (lg) printf("sum_s : %f , s sth %f\n", sum_s,  v(c->stage_threshold, nb_s));
   // if(fail) printf("Feature: %d stage raté",nb_f,nb_s);
    //else printf("Feature: %d reussi stage %d",nb_f,nb_s);
    nb_s++;
  }

  return !fail;
}


void message_erreur(void)
{
  //fprintf(sortie,"obj_detect_Haar \n");
  printf("Erreur dans la détection");
}

void  termine_programme(void){}








































