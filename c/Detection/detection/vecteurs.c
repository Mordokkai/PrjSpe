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

int SORTIE =0;//Variable globale pour les noms des fichiers de sortie

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

void ecrire_image_pgm(MI* mi, char* nomimg){
    printf("Les dimensions du MI sont: %d %d \n",mi->dim1,mi->dim2);
    int i=0;
    FILE*f =fopen(nomimg,"w");
    fprintf(f,"P2\n%d %d\n255\n",mi->dim1,mi->dim2);
    int* p=mi->coeffs;
    for(i=0;i<mi->dim2;i++){
        int j=0;
        for(j=0;j<mi->dim1;j++){
            fprintf(f,"%d ", *(p++));
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


MI* construit_Image_Integrale(MI* image){
    /**On recupère l'image intégrale**/
	int32_t* int_image = integral_image(image->coeffs, image->dim1, image->dim2);
	/**On la met dans la matrice**/
	MI* mi= MI_alloue_special(1,image->dim1,image->dim2);
	mi->coeffs=int_image;
	return mi;
}

MI* construit_Image_Integrale_Carre(MI* image){
    /**On recupère l'image intégrale**/
	int32_t* square_int=integral_image_carre(image->coeffs, image->dim1, image->dim2);
	/**On la met dans la matrice**/
	MI* mi= MI_alloue_special(1,image->dim1,image->dim2);
	mi->coeffs=square_int;
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
    i=0;
    for(i=p.x;i<p.x+c.d.x;i++){
        int z=p.y+c.d.y;
        m(mi,i,z)=250;
    }
}

int* lire_entree_IM(FILE* f, int* width, int* height, int* lumin){
    char tmp[10];
    fscanf(f,"%s %d %d %d",tmp,width,height,lumin);
    int i=0;
    int* mi=calloc(*width* *height,sizeof(int));
    int* q=mi;
    for(i=0;i<*width* *height;i++){
        fscanf(f,"%d",q);
        q++;
    }
    return mi;
}

void ecrire_sortie_II(FILE* f, int* mi){
    //fprintf(f,"P2\n%d %d\n255",mi->dim1,mi->dim2);
    int* p=mi;
    int i=0;
   while(i<160*120){
        fprintf(f,"%d\n",*p);
        p++;
        i++;
   }
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
    for(i=0;i<(int)(img->dim1*img->dim2);i++){
        cadre->coeffs[i]+=img->coeffs[i];
    }
    return cadre;
}

void out_visage(MI* mi_img, Pixel* p, int nb_Cadres, Haar_Cascade c){
    printf("Affichage des données lues");
    MI* mi= MI_alloue_special(1,mi_img->dim1,mi_img->dim2);
    int i=0;
    while(i< nb_Cadres){
        colorer_Pixel(mi,*p,c);
        p++;
        i++;
    }
    char carac = 'a'+SORTIE;
    SORTIE++;
    char addc[11]={'r','e','s','u','l','t','a','t','/',carac,'\0'};
    mi=fusion_cadre_image(mi_img,mi);
    ecrire_image_pgm(mi,addc);
}




/**Les fonctions principales de l'algorithme**/

void Haar_Cascade_read_list(Haar_Cascade *c, FILE *file)
{
    int rect_n, feat_n, s_n; //nombre total de rectangle, feature, stage
    char tmp[256];
    int i;

    fscanf(file, "%s %d %d", tmp, &c->d.x, &c->d.y); //taille zone
    fscanf(file, "%s %d", tmp, &rect_n);
    fscanf(file, "%s %d", tmp, &feat_n);
    fscanf(file, "%s %d", tmp, &s_n);

    //Init
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
    }
    if (x>=0){
        r-=m(m, x, y1);
    }
    if (y>=0){
        r-=m(m, x1, y);
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

                sum_f += v(c->weight, nb_r) *val;	//Pondération
                nb_r++;
            }

      float th = m(c->feature_threshold, 0, nb_f);
      float t = th*th*variance_sq;
      //   Test les features de l'étage
      int test = (sum_f*sum_f) >= t;
      int alpha;
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
      nb_f++;
    }
    // Test l'étage
    fail = (sum_s < v(c->stage_threshold, nb_s));
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

