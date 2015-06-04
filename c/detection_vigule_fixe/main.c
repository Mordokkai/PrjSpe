#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include "detector.h"
#include "fixed_point.h"


#define PRINTTAB2(tab, n,e) {\
                            for(int z=n-1; z>=0; z-- ) \
                                { \
                                    printf("%d", tab[z]);\
                                    if(z==n-1-e) printf("|");\
                                }\
                            printf("\n");\
                          }
void convertCascade(Cascade cascade, char* outname, int se, int sv,int fe, int fv, int gte, int gtv, int lse, int lsv)
{
    FILE* f = fopen(outname, "w+");
    StageList s=cascadeToStageList(&cascade);
    StageList p;
    for (p=s; p!=NULL; p=p->next)
    {
        char c;
        for(int i=0; i<p->element.numberOfFeatures; i++)
        {
            c ='R';
            for(int j=0; j<p->element.features[i].type; j++)
            {
                int x,y,w,h,weight;
                x=p->element.features[i].rect[j].x;
                y=p->element.features[i].rect[j].y;
                w=p->element.features[i].rect[j].weight;
                h=p->element.features[i].rect[j].h;
                weight=(int)p->element.features[i].rect[j].weight;
                fprintf(f,"%c %d %d %d %d %d\n",c, x, y, w, h, weight);


            }
            c='F';
            FixedPoint fth, gt, ls;
            initFixedPoint(&fth, fe,fv);
            initFixedPoint(&gt, gte, gtv);
            initFixedPoint(&ls, lse,lsv);
            convertDouble(p->element.features[i].f,&fth);
            convertDouble(p->element.features[i].gt,&gt);
            convertDouble(p->element.features[i].ls,&ls);
            fprintf(f, "%c %d %d %d\n",c, fth.val, gt.val, ls.val);
        }
        c='S';
        FixedPoint sth;
        initFixedPoint(&sth, se, sv);
        convertDouble(p->element.threshold,&sth);
        fprintf(f, "%c %d", c, sth.val);
    }
}

int main(int argc, char ** argv)
{
    printf("Hello world!\n");
    double sth,fth,gt,ls;
    Cascade* cascade =openCascade(argv[1]);
    maxThresholds(*cascade,&sth,&fth,&gt,&ls);
    printf("%lf %lf %lf %lf\n",sth,fth,gt,ls);

    int se = minE(sth);
    int sv = SIZE-se-1;
    int fe = minE(fth);
    int fv = SIZE-fe-1;
    int gte = minE(gt);
    int gtv = SIZE-gte-1;
    int lse = minE(ls);
    int lsv = SIZE-lse-1;

    printf("\n%d %d %d %d\n", se, fe, gte, lse);
    convertCascade(*cascade,"test.txt",se,sv,fe,fv,gte,gtv,lse,lsv);


//    FixedPoint fx1, fx2;
//    bool init1 = initFixedPoint(&fx1, 5,8);
//    bool init2 = initFixedPoint(&fx2,3,6);
//    if (!init1 || !init2)
//        printf("Not sufficient!!!\n");
//
//    convertDouble(-4 ,&fx1);
//    convertDouble(-4, &fx2);
    minE(8.);
    //printf("%d");
    //int* fx2tab = fixedPointtoTab(fx2);
    //PRINTTAB2(fx2tab, 10,3);

//    FixedPoint result = PLUS(fx1, fx2);
    return 0;
}
