// Auteur : Stephane MANCINI
// stephane.mancini@grenoble-inp.fr
//
#include "base.h"
#include "parametre.h"
#include "image.h"
#include "kern_affine.h"

#include "kern_mipmap.h"
#include "kern_img_integral.h"

typedef struct Haar_Cascade {
  Pixel d;
  float area, inv_area; //area c'est l'aire supérieure gauche du pixel
  MI *rect;
  Vr *weight;
  VI *feature_rect;
  Mr *feature_threshold;
  VI *stage_feature;
  Vr *stage_threshold;

} Haar_Cascade;


/*Fonctions manquantes
vn(*stage_feature) renvoie le nombre de stages
v(*stage_feature,int s) renvoie le nombre de feature dans le stage d'indice s
v(*stage_feature_rect,nb_f) renvoie le nombre de rectangles dans le feature d'indice nb_f
*/

//tableau àune dimension de int32_t 32 bits





void Haar_normalize_rects(Haar_Cascade *c)
{
  unsigned int nb_rect0;
  unsigned int nb_f = 0;
  unsigned int nb_r = 0;
	//On parcourt tous les stages (Sy)
  for (unsigned int s = 0; s < vn(c->stage_feature); s++) {
		//On parcourt tous les haarfeatures de ce stage (Sy)
    for (unsigned int f = 0; f < v(c->stage_feature, s); f++) {
      nb_rect0 = nb_r;
      float sum0 = 0;
			//Parcourt des rectangles de la feature
      for (unsigned int r = 0; r < v(c->feature_rect, nb_f); r++) {
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
  Vr_affiche(1, c->weight , "weight :");
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
  Haar_normalize_rects(c);


#define PREC 16
  //#define vfixe(a,prec) (trunc((a)*pow(2,prec)))/pow(2,prec)

#define vfixe(a,prec) a

    int j,k;
    for(i=0;i<vn(c->weight);i++)
      v(c->weight, i)= vfixe(v(c->weight, i), 14);

    for(j=0;j<mn1(c->feature_threshold);j++)
      for(i=0;i<mn0(c->feature_threshold);i++)
        m(c->feature_threshold, i, j) = vfixe( m(c->feature_threshold, i, j), PREC);

    for(i=0;i<vn(c->stage_threshold);i++)
      v(c->stage_threshold, i)= vfixe(v(c->stage_threshold, i), PREC);

}





/* calcul l'intégrale sur un carre de coin x, y et de largeur (tx,ty) */
int img_int_rect_eval(MI *m, int x , int y, int tx, int ty)
{
//L4-L3-L2+L1
  int r=0;
  x=x-1; y=y-1;
  int x1=x+tx, y1=y+ty;
  if (x>=0 && y>=0)
    r+= m(m, x, y);
  if (x>=0)
    r-=m(m, x, y1);
  if (y>=0)
    r-=m(m, x1, y);
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
    for (unsigned int f = 0; f < v(c->stage_feature, nb_s); f++) {
      float sum_f = 0;

      // Parcours des rectangles de la feature actuelle et
      // evaluation de ces rectangles sur l'image integrale
      for (unsigned int r = 0; r < v(c->feature_rect, nb_f); r++) {
        int val= img_int_rect_eval(img_int,
                                   o.x+m(c->rect, 0, nb_r),
                                   o.y+m(c->rect, 1, nb_r),
                                   m(c->rect, 2, nb_r),
                                   m(c->rect, 3, nb_r)
                                   );
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
    nb_s++;
  }

  return !fail;
}






void message_erreur(void)
{
  fprintf(sortie,"obj_detect_Haar \n");
}






void  termine_programme(void){}






int main(int argc, char **argv)
{
  char nomimg[255];
  Image *image;
  MI *m;
  MI *r;
  Mr *tr;
  FILE *trf;	//Pointeur vers le fichier contenant les seuils

  parametre_verbose=sortie=sortie_verbose=erreur=stdout;
  SEUIL_ZERO=1e-6;
  if (argc==1)
    {
      printf("usage : obj_detect_Haar  Haar_cascade.list img \n");
      exit(0);
    }
  /* Des bricoles d'initialisation */
  Texte_initialise(5);

  printf("Go!");
  fflush(stdout);
  strcpy(nomimg,argv[2]);

  FILE *f_c=ouvre_fichier_lecture("", argv[1], "r");
	//On crée la structure de cascade à partir du fichier texte
  Haar_Cascade c;
  Haar_Cascade_read_list(&c, f_c);
  fclose(f_c);
  printf("Haar OK!\n");fflush(stdout);


	//On va créer l'image intégrale
  MI8u *m8u;	//????????????
  int i,j;
  /* lit l'image d'entrée */
  m8u=MI8u_lit_image(NULL, nomimg);
  printf("Img OK!\n");fflush(stdout);
  //MI8u_visualise(m8u, 1 , "&", "img");
  /* convertit en 32 bits */
  m=MI_alloue_special(1, mn0(m8u),  mn1(m8u));
  toMxx(m, m8u);

  M3I *mipmapiso;
  MI_taille triso;
  float scale=0.83;
  int filter_threshold=12;
  int filter_size=6;

  int  scale_level=-log(min(mn0(m)/(c.d.x+2), mn1(m)/(c.d.y+2)))/log(scale)+1;

  int level=-scale_level*log(scale)/log(2)+2;

  printf("scale_level=%d level=%d\n", scale_level, level);
  mipmapiso=M3I_alloue_special(1, mn0(m), mn1(m), level);
  /* Construit la mipmap qui  servira pour tous les niveaux d'échelle */
  mipmap_gen_iso_MI(mipmapiso, triso,  m, level);
  //M3I_visualise(mipmapiso, 1 , "&", "mipmapiso");
  /* Allocations diverses */
  MI *scaled, *scaled_int, *scaled_sq, *scaled_sq_int, *mt;
  MI *detect;
  MI8u  *detect_filled;
  M3I8u *detect_binary,*detect_binary_filtered,*detect_binary_filled;
  VI *cpt_y;
  scaled=MI_alloue_special(1, mn0(mipmapiso),  mn1(mipmapiso));
  scaled_int=MI_alloue_special(1, mn0(mipmapiso),  mn1(mipmapiso));
  scaled_sq=MI_alloue_special(1, mn0(mipmapiso),  mn1(mipmapiso));
  scaled_sq_int=MI_alloue_special(1, mn0(mipmapiso),  mn1(mipmapiso));
  mt=MI_alloue_special(1, mn0(mipmapiso),  mn1(mipmapiso));
  detect=MI_alloue_special(1, mn0(mipmapiso),  mn1(mipmapiso));
  detect_filled=MI8u_alloue_special(1, mn0(mipmapiso),  mn1(mipmapiso));

  detect_binary=M3I8u_alloue_special(1, mn0(mipmapiso),  mn1(mipmapiso), scale_level);
  detect_binary_filtered=M3I8u_alloue_special(1, mn0(mipmapiso),  mn1(mipmapiso), scale_level);
  detect_binary_filled=M3I8u_alloue_special(1, mn0(mipmapiso),  mn1(mipmapiso), scale_level);
  cpt_y=VI_alloue_special(1, mn0(mipmapiso));

  M3I8u_zero(detect_binary);
  M3I8u_zero(detect_binary_filtered);
  M3I8u_zero(detect_binary_filled);
  VI_zero(cpt_y);
  MI_cst(detect, 128);
  float sc;
  int s;

  sc=1.0;

  M3I8u *pyr;
  pyr=M3I8u_alloue_special(1,  m3n0(detect_binary),  m3n1(detect_binary),  scale_level);
  M3I8u_zero(pyr);
  M4I *intcarre;
  intcarre=M4I_alloue_special(1,  m3n0(detect_binary),  m3n1(detect_binary),  m3n2(detect_binary), 2);
  M4I_zero(intcarre);
/*???????????????????????*/




  /* Parcours tous les niveaux d'échelle */
  printf("Echelle\n");
  for(s=0;s<scale_level;s++)
    {
      printf("s=%d\n",s);
      /* Construit  chaque niveau à partir de la mipmap */
      scale_from_mipmap_iso_img_MI(scaled, mipmapiso , triso,  sc);
      /* Calcule le carre, l'image intégrale et l'image intégrale du carre */
      MI_carre(scaled_sq, scaled);
      img_integral_MI(scaled_int, scaled);
      img_integral_MI(scaled_sq_int, scaled_sq);
      for(int ii=0; ii<m4n0(intcarre);ii++)
        for(int jj=0; jj<m4n1(intcarre);jj++)
          {
            m3(pyr, ii, jj, s)=m(scaled, ii, jj);
            m4(intcarre, ii, jj, s, 0)=m(scaled_int, ii, jj);
            m4(intcarre, ii, jj, s, 1)=m(scaled_sq_int, ii, jj);
          }
      int  r;
      Pixel o;
      printf("Haar evaluate\n");
      /* Pour tous les pixels de l'image, detecte une zone */
      for(o.y=0; o.y<mn1(scaled)-c.d.y;o.y++)
        for(o.x=0; o.x<mn0(scaled)-c.d.x;o.x++)
          {
            //    if (  (o.x+ o.y*mn0(scaled))%1000==0)
            // printf("%d %d\n", o.x, o.y);
            if (Haar_evaluate(&c, scaled_int, scaled_sq_int, o))
              {
                m3(detect_binary, o.x, o.y, s)=255;
                /* si trouve une zone, ajoute nbre de détections (*2)*/
                int i,j;
                for(i=0;i<c.d.x/sc;i++)
                  for(j=0;j<c.d.y/sc;j++)
                    m(detect, (int)(o.x/sc+i), (int)(o.y/sc+j))+=10;
              }
          }

          }
      sc*=scale;
    }
 M3I8u_ecrit_image_P5(detect_binary, "res/detect_binary.pgm");
  M3I8u_ecrit_image_P5(detect_binary_filtered, "res/detect_binary_filtered.pgm");
  Mxxmul(detect_filled, detect_filled, mipmapiso);
  //MI8u_visualise(detect_filled, 1, "&", "detect_filled");
  MI8u_ecrit_image_P5(detect_filled, "res/detect_filled.pgm");
  M3I8u_ecrit_image_P5(pyr, "res/pyr.pgm");
  M4I_ecrit_image_P5(intcarre, "res/intcarre.pgm");

}
