#include<stdio.h>
#include<stdlib.h>

#include"detector.h"
#include"inttypes.h"
#include"math.h"
#include"stdbool.h"

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

            if(fscanf(f,"%d %d", &cascade->width, &cascade->height)!=2)
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


void maxThresholds (Cascade cascade, double * sth, double *fth, double* fgt, double* fls){
    FILE *f = cascade.file;

    *sth=0;
    *fth=0;
    *fgt=0;
    *fls=0;

    fpos_t curPos;
    fgetpos(f, &curPos);

    double th1=0, th2=0, th3=0, th4=0;
    int x,y,w,z;
    double t;

    char c;
    while(!feof(f)){
        c = fgetc(f);
        if(c=='R')
            fscanf(f,"%d %d %d %d %lf",&x,&y,&w,&z,&t);
        if(c=='F')
        {
            fscanf(f,"%lf %lf %lf", &th1, &th2, &th3);
            //fgetc(f);
        }
        if (c=='S')
        {
            fscanf(f, "%lf", &th4);
            //printf("%lf\n", th4);
            fgetc(f);
        }


        if(fabs(th1)>*fth)
            *fth = fabs(th1);
        if(fabs(th2)>*fgt)
            *fgt = fabs(th2);
        if(fabs(th3)>*fls)
            *fls = fabs(th3);
        if(fabs(th4)>*sth)
            *sth = fabs(th4);
        c=fgetc(f);
    }
    fsetpos(f,&curPos);
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
    fscanf(cascade->file,"%lf", &s.threshold);
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
                fscanf(cascade->file,"%d %d %d %d %lf",&tmp[rcount].x, &tmp[rcount].y, &tmp[rcount].w, &tmp[rcount].h, &tmp[rcount].weight );
                rcount++;
            }
        if(c=='F')
            {
                s.features[fcount].rect=(Rectangle*)malloc(sizeof(Rectangle)*rcount);
                for (int i=0; i<rcount; i++)
                    s.features[fcount].rect[i]=tmp[i];
                s.features[fcount].type=rcount;
                fscanf(cascade->file,"%lf %lf %lf", &s.features[fcount].f, &s.features[fcount].gt, &s.features[fcount].ls);
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
            fprintf(stdout,"%d %d %d %d %lf\n", stage.features[i].rect[j].x, stage.features[i].rect[j].y,
                stage.features[i].rect[j].w, stage.features[i].rect[j].h, stage.features[i].rect[j].weight);
        }
        fprintf(stdout,"%lf %lf %lf\n", stage.features[i].f, stage.features[i].gt, stage.features[i].ls);
        fprintf(stdout,"\n");
    }
    fprintf(stdout,"%lf\n**********************\n", stage.threshold);

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
