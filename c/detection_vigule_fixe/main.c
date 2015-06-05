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
    fpos_t pos;
    fgetpos(cascade.file,&pos);
    StageList s=cascadeToStageList(&cascade);
    StageList p;
    fprintf(f,"#SE %d SV=%d\n#FE=%d FV=%d\n#GTE=%d GTV=%d\n#LSE=%d LSV=%d\n", se, sv, fe, fv, gte, gtv, lse, lsv);
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
                w=p->element.features[i].rect[j].w;
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
    fsetpos(cascade.file,&pos);
    fclose((f));
}
char* intToBinary(int a, int size) // a<2^size
{
    char* result = calloc(size+1, sizeof(char));
//    int size=minE(((double) a));
//    printf("size=%d\n", size);
    if(a>=0)
    {
        for(int i = size-1; i>=0; i--,a=a/2)
            result[i]='0'+ (a%2);
            return result;
    }
    else
    {
        a=-a;
        for(int i = size-1; i>=0; i--,a=a/2)
            result[i]='0'+ (a%2);
//        for(int i = size-1; i>=0; i--,a=a/2)
//            result[i]='0'+ ((a%2)+1)%2;

        result[0]='1';

//        int p=1;
//        a=0;
//        for( int i =size-1; i>=0; i--, p*=2)
//        {
//            a+=result[i]*p;
//        }
//        result = intToBinary(a,size);
    }

    return result;


}

void generateBinaryVHDL(Cascade cascade, char* outname, int se, int sv,int fe, int fv, int gte, int gtv, int lse, int lsv)
{
    FILE* f = fopen(outname, "w+");
    fpos_t pos;
    fgetpos(cascade.file,&pos);
    StageList s=cascadeToStageList(&cascade);
    StageList p;
    int fadress=0;
    int radress=0;
    int sadress=0;
    fprintf(f,"--Stages--\n(\n");
    for (p=s; p!=NULL; p=p->next, sadress++)
    {

        FixedPoint sth;
        initFixedPoint(&sth, se, sv);
        convertDouble(p->element.threshold,&sth);
        char*sthb= intToBinary(sth.val,16);
        char* fadressb = intToBinary(fadress, 12);
        fprintf(f, "%d => \"%s%s\",\n", sadress, sthb,fadressb);
        fadress+=p->element.numberOfFeatures;
    }
    fprintf(f,");\n--Features--\n(\n");
    for (fadress=0, p=s; p!=NULL; p=p->next)
    {
        for(int i=0; i<p->element.numberOfFeatures; i++, fadress++)
        {

            FixedPoint fth, gt, ls;
            initFixedPoint(&fth, fe,fv);
            initFixedPoint(&gt, gte, gtv);
            initFixedPoint(&ls, lse,lsv);
            convertDouble(p->element.features[i].f,&fth);
            convertDouble(p->element.features[i].gt,&gt);
            convertDouble(p->element.features[i].ls,&ls);
            char* fthb =intToBinary(fth.val, 16);
            char* gtb = intToBinary(gt.val,16);
            char* lsb = intToBinary(ls.val, 16);
            char* radressb= intToBinary(radress,13);
            fprintf(f,"%d => \"%s%s%s%s\",\n", fadress,fthb,gtb,lsb,radressb);
            radress+=p->element.features[i].type;

        }
    }
    fprintf(f,");\n--Rectangles--\n(\n");

     for (radress=0,p=s; p!=NULL; p=p->next)
    {
        for(int i=0; i<p->element.numberOfFeatures; i++)
        {
            for(int j=0; j<p->element.features[i].type; j++, radress++)
            {
                char* xb,*yb,*wb,*hb,*weightb;
                int x, y, w,h,weight;
                x=p->element.features[i].rect[j].x;
                y=p->element.features[i].rect[j].y;
                w=p->element.features[i].rect[j].w;
                h=p->element.features[i].rect[j].h;
                weight=(int)p->element.features[i].rect[j].weight;
                //printf("waight=%d\n", weight);

                xb=intToBinary(x,5);
                yb=intToBinary(y,5);
                wb=intToBinary(w,5);
                hb=intToBinary(h,5);
                weightb=intToBinary(weight,5);
                fprintf(f,"%d => \"%s%s%s%s%s\",\n",radress, xb, yb, wb, hb, weightb);


            }
        }
    }
    fsetpos(cascade.file,&pos);
     fprintf(f,");\n");
     fclose(f);
}

int main(int argc, char ** argv)
{
    printf("Hello world!\n");
//    if(argc<4)
//        return 1;
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
    convertCascade(*cascade, "test2.txt",se,sv,fe,fv,gte,gtv,lse,lsv);
    generateBinaryVHDL(*cascade, "test.txt",se,sv,fe,fv,gte,gtv,lse,lsv);
//    char *c = intToBinary(3,4);
//    printf("%s", c);

    return 0;
}
