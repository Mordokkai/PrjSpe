#include<stdbool.h>
#include<stdlib.h>
#include<stdio.h>
#include"detector.h"
#include"pgm.h"
#include"integralpgm.h"

Cascade* openCascade(char* filename){

    Cascade* cascade = malloc(sizeof(Cascade));
    FILE* f = fopen(filename, "r");
    if(f==NULL)
    {
        printf("Error reading the file");
        return NULL;
    }
    char c;
parse: //ignoring comments
    c = fgetc(f);
    if(c =='#')
    {
        while(fgetc(f)!='\n');
        goto parse;
    }
    else if(c=='D'){

            if(fscanf(f,"%d %d", &cascade->D.width, &cascade->D.height)!=2)
                {
                    printf("Inclomplet cascade");
                    return NULL;
                }
    }
    else
        {
            printf("Incorrect file");
            return NULL;
        }
    c=fgetc(f);// position at the start of the first stage

    cascade->file = f;

    return cascade;


}


Stage loadNextStage(Cascade* cascade){


    Stage s;
    fpos_t curpos;
    fgetpos(cascade->file, &curpos);// store the current position in the file
    fpos_t nextpos;
    uint16_t fcount=0;

    //first we count the number of feature per stage
    char c;
    do
    {
            c=fgetc(cascade->file);
            if (c=='F')
                fcount ++;
    }while(c!='S' && !feof(cascade->file));
    if(feof(cascade->file))
        printf("ERRoR");

    // c='S'; see if it's the last stage
    fscanf(cascade->file,"%llf", &s.threshold);
    s.numberOfFeatures=fcount;
    //while(fgetc(cascade->file)==' ');

    c=fgetc(cascade->file);
    c=fgetc(cascade->file);

    if(feof(cascade->file))
        s.last=true;
    else
    {
        s.last=false;
        fseek(cascade->file,-1,SEEK_CUR);
    }


    fgetpos(cascade->file, &nextpos);

    //creation the features;
    s.features=(Feature*)malloc(sizeof(Feature)*fcount);
    fsetpos(cascade->file,&curpos);
    Rectangle tmp[4];
    uint16_t rcount=0;
    fcount =0;
    do
    {
        c=fgetc(cascade->file);
        if(c=='R')
            {
                fscanf(cascade->file,"%d %d %d %d %llf",&tmp[rcount].x, &tmp[rcount].y, &tmp[rcount].w, &tmp[rcount].h, &tmp[rcount].weight );
                rcount++;
            }
        if(c=='F')
            {
                s.features[fcount].rect=(Rectangle*)malloc(sizeof(Rectangle)*rcount);
                for (int i=0; i<rcount; i++)
                    s.features[fcount].rect[i]=tmp[i];
                s.features[fcount].type=rcount;
                fscanf(cascade->file,"%llf %llf %llf", &s.features[fcount].f, &s.features[fcount].gt, &s.features[fcount].ls);
                rcount=0;
                fcount++;

            }

    }while(c!='S');
    fsetpos(cascade->file,&nextpos);
    return s;
}

void printStage(Stage stage){

    fprintf(stdout,"**********************\n");
    //printf("feartures :%d\n", stage.numberOfFeatures);
    for(int i =0; i<stage.numberOfFeatures; i++)
    {

        for (int j =0; j<stage.features[i].type; j++)
        {
            fprintf(stdout,"%d %d %d %d %llf\n", stage.features[i].rect[j].x, stage.features[i].rect[j].y,
                stage.features[i].rect[j].w, stage.features[i].rect[j].h, stage.features[i].rect[j].weight);
        }
        fprintf(stdout,"%llf %llf %llf\n", stage.features[i].f, stage.features[i].gt, stage.features[i].ls);
        fprintf(stdout,"\n");
    }
    fprintf(stdout,"%llf\n**********************\n", stage.threshold);

}

long double rectangleEvaluation(Rectangle r, Detector d, integralPgm* ii){


    int32_t ax = d.x+r.x-1;
    int32_t ay = d.y+r.y-1;
    int32_t bx= ax + r.w;
    int32_t by=ay;
    int32_t cx=ax;
    int32_t cy=ay+r.h;
    int32_t dx=bx;
    int32_t dy=cy;

    if(ax>=0 && ay>=0)
        //return (ii->values[dx][dy] + ii->values[ax][ay] -  ii->values[bx][by] -  ii->values[cx][cy])*r.weight;
        return (ii->values[dy][dx] + ii->values[ay][ax] -  ii->values[by][bx] -  ii->values[cy][cx])*r.weight;
    else if (ay>=0)
        //return (ii->values[dx][dy] - ii->values[bx][by])*r.weight;
        return (ii->values[dy][dx] - ii->values[by][bx])*r.weight;
    else
//        return (ii->values[dx][dy] - ii->values[cx][cy])*r.weight;
        return (ii->values[dy][dx] - ii->values[cy][cx])*r.weight;



}
long double featureEvalution(Feature f, Detector d, integralPgm* ii, integralPgm* ii_sq)
{
    long double value = 0;
    for (int i=0; i<f.type; i++)
        value+= rectangleEvaluation(f.rect[i],d,ii);

    double variance_sq;
    double mean;

    Rectangle r;
    r.x=0;
    r.y=0;
    r.h=d.window.height;
    r.w=d.window.width;
    r.weight=1;

    double s=r.h*r.w;

    mean=rectangleEvaluation(r,d,ii);
    variance_sq=-(mean*mean - rectangleEvaluation(r,d,ii_sq));

    bool test = value*value >= f.f*f.f*variance_sq;

    int alpha;

    if (value>= 0 )
        {
          if (f.f>=0)
            alpha= test ? 1 : 0;
          else
            alpha=1;
        }
    else
        {
          if (f.f>0)
            alpha= 0;
          else
            alpha= (!test) ? 1 : 0;
        }

    if(!alpha)
        value+=f.gt;
    else
        value+=f.ls;
    return value;
}

long double stageEvaluation(Stage stage, Detector detector, integralPgm* ii, integralPgm* ii_sq){

    long double value =0;
    for (int i=0; i<stage.numberOfFeatures; i++)
        value+= featureEvalution(stage.features[i],detector,ii, ii_sq);
    return value;

}

bool hasPassedStage(Stage stage, Detector detector, integralPgm* ii, integralPgm* ii_sq){
    return stageEvaluation(stage, detector, ii, ii_sq)>= stage.threshold;
}


StageList addStageList(StageList l, Stage e)
{
    StageList p,q;
    p = (StageList)malloc(sizeof(*p));
    p->element=e;
    p->next=NULL;
    if(l==NULL)
    {

        return p;
    }
    else
    {
        for(q=l; q->next!=NULL;q=q->next);
        q->next=p;
    }
    return l;
}

StageList cascadeToStageList(Cascade *cascade)
{
    StageList l=NULL;
    Stage e;
    while(!e.last)
    {
        e=loadNextStage(cascade);
        l=addStageList(l,e);
    }
    return l;
}

void printStageList(StageList l)
{
    StageList p;
    for(p=l;p!=NULL; p=p->next)
    {
        printStage(p->element);
    }
}

bool moveDetector(Detector* d, uint16_t width, uint16_t height)
{
    if(d->y+d->window.height>=height && d->x +d->window.width>=width)
        return true;

    else if (d->x+d->window.width==width)
    {
        d->x=0;
        d->y++;
        return false;
    }
    else
    {
        d->x++;
        return false;
    }
}

void scanPgm(Cascade* cascade, pgmFormat *i, char* resultName)
{

        Detector d;
        d.window= cascade->D;
        d.x=0;
        d.y=0;
        //d.window.height=7;
        integralPgm ii, ii_sq;

        pgmFormat result = *i;
        ii= generateIntegralPgm(*i);
        ii_sq=generateIntegralPgm_sq(*i);

        StageList l = cascadeToStageList(cascade);
        StageList p;
        //int stageNumber;
        bool stageStatus;
        do{
            //printf("DETECTOR %d %d", d.x, d.y);
            for(p=l; p!=NULL; p=p->next)
            {
                stageStatus = hasPassedStage(p->element,d,&ii,&ii_sq);
                if(stageStatus && p->next==NULL)
                    {
                        //face detected
                        printf("Face detected: %d %d\n", d.x, d.y);
                        printDetector(d,&result);
                    }
                if(!stageStatus)
                    break;
            }

        }while(!moveDetector(&d,ii.width,ii.height));
        savePgm(result,resultName);
}



void printDetector(Detector d, pgmFormat* pgm){
    //int i,j;
    pgm->values[d.y+ d.window.height/2][d.x+d.window.width/2]=255;
}


