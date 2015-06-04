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
void convertCascade(Cascade cascade, char* outname, int se, int sv,int fe, int fv)
{
    StageList s=cascadeToStageList(&cascade);
    StageList p;
    for (p=s; p!=NULL; p=p->next)
    {

    }
}

int main(int argc, char ** argv)
{
    printf("Hello world!\n");
//    double a,b,c,d;
//    Cascade* cascade =openCascade(argv[1]);
//    maxThresholds(*cascade,&a,&b,&c,&d);
//    printf("%lf %lf %lf %lf\n",a,b,c,d);
//
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
