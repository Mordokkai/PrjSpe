#include <stdlib.h>
#include <stdio.h>
#include "detection.h"
#include "ajout.h"
#include "vecteurs.h"
#include "../../image_integrale/image_integrale.h"
#include <math.h>


/** MACROS **/

#define min(X, Y) (((X) < (Y)) ? (X) : (Y))
#define v(a,i) a->coeffs[i]
#define mn0(a) a->dim1
#define mn1(a) a->dim2
#define vn(a) a->dim



int main(int argc, char **argv) {


    char nomimg[255];

    if (argc==1)
    {
        printf("usage : obj_detect_Haar  Haar_cascade.list img \n");
        exit(0);
    }

    printf("Go!");
    printf("%s",argv[2]);
    strcpy(nomimg,argv[2]);

    FILE *f_c=fopen(argv[1], "r");
    if(f_c==NULL){printf("Ne trouve pas le classifier");}

	/** On crée la structure de cascade à partir du fichier texte **/
    Haar_Cascade c;
    Haar_Cascade_read_list(&c, f_c);
    fclose(f_c);
    printf("Haar OK!\n");

    float scale=0.95;
    MI *scaled, *scaled_int, *scaled_sq, *scaled_sq_int, *mt;
    float sc=1.0;
    int s;

    /** lire l'image une premiere fois**/
    FILE* f_in=fopen(nomimg,"r");
    int width,height,lumin;
    int* image_c=lire_entree_IM(f_in,&width,&height,&lumin);
    MI* image=MI_alloue_special(1,width,height);
    image->coeffs=image_c;
    int  scale_level=-log(min(mn0(image)/(c.d.x+2), mn1(image)/(c.d.y+2)))/log(scale)+1;
    int level=-scale_level*log(scale)/log(2)+2;
    printf("scale_level=%d level=%d\n", scale_level, level);

    /** Parcours tous les niveaux d'échelle **/
    float coeff_mult=1;
    for(s=0;s<scale_level;s++)
    {
        /**On scale**/
        coeff_mult=coeff_mult*sc;
        printf("s=%d, coeff=%f\n",s,coeff_mult);
        MI* image_sc;
        int* image_sc_i;
        image_sc_i=scaling(image->coeffs,image->dim1,image->dim2,(int)(image->dim1*coeff_mult),(int)(image->dim2*coeff_mult));
        printf("Fini scale");
        image_sc=MI_alloue_special(1,(int)(image->dim1*coeff_mult),(int)(image->dim2*coeff_mult));
        image_sc->coeffs=image_sc_i;

        /**On construit les images intégrals**/
        scaled_int=construit_Image_Integrale(image_sc);
        scaled_sq_int=construit_Image_Integrale_Carre(image_sc);
        if(s==0){
            FILE* g=fopen("img_II.txt","w");
            ecrire_sortie_II(g,scaled_int->coeffs);
            FILE* h=fopen("img_II_2.txt","w");
            ecrire_sortie_II(h,scaled_sq_int->coeffs);
        }
        /**On évalue**/
        Pixel o;
        Pixel* cadres=calloc(200000,sizeof(Pixel)); /**Il est fort improbable d'avoir plus de 2000 cadres détéctés**/
        printf("Haar evaluate\n");
        int cpt=0;
        printf("Image de : %d %d",mn1(scaled_int),mn0(scaled_int));
        for(o.y=0; o.y<mn1(scaled_int)-c.d.y;o.y++){
            for(o.x=0; o.x<mn0(scaled_int)-c.d.x;o.x++)
            {
                if (Haar_evaluate(&c, scaled_int, scaled_sq_int, o))
                {
                    printf("DETECTE %d %d", o.x, o.y);
                    Pixel p;
                    p.x=o.x;
                    p.y=o.y;
                    cadres[cpt]=p;
                    cpt++;
                }
            }
        }
        printf("Il y a: %d cadres détéctés.",cpt);
        out_visage(image_sc, cadres, cpt, c);
        sc*=scale;
    }
}






