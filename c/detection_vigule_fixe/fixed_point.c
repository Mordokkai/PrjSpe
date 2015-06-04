#include<stdio.h>
#include<stdlib.h>
#include"math.h"
#include"detector.h"
#include"fixed_point.h"
#include<stdbool.h>


#define POW(X,a) {\
                    if(a>=0)\
                        for(int z=0; z<a; z++) \
                                X*=2; \
                    else\
                        for(int z=0; z<-a; z++) \
                                X/=2; \
                 }

#define PRINTTAB(tab, n,e) {\
                            for(int z=n-1; z>=0; z-- ) \
                                { \
                                    printf("%d", tab[z]);\
                                    if(z==n-1-e) printf("|");\
                                }\
                            printf("\n");\
                          }


bool initFixedPoint(FixedPoint* fx, int e, int v)
{
    fx->e=e;
    fx->v=v;
    if (e+v>SIZE-1)
        return false;
    else
        return true;
}

bool convertDouble(double x, FixedPoint* fx)
{
    int min=-1;
    double max=-1;

    for (int i=0; i<fx->e; i++)
    {
        min*=2;

    }
    for (int i =0; i<fx->v; i++)
        max/=2;

    max=(double)-min + max;

    if(x<min)
        {
            fx->val=min;
            return false;
        }
    if(x>max)
        {
            fx->val= max;
            return false;
        }

    int valTab[SIZE];
    for (int i=0; i <SIZE; i++)
    {
        valTab[i]=0;
    }

    double X =0;


    if(x<0)
    {
        valTab[SIZE-1]=1;
        X=-1;
        POW(X, fx->e);
    }
    double p=1;
    double lastp=1;
    int a;
    int j=0;
    int i=0;
    for (i = fx->e-1, j=SIZE-2; i>= -fx->v; i--, j--)
    {
        a=i;
        POW(p,a)
        if(X+p<=x)
        {
            if(fabs(x-X-p)<=fabs(x-X-lastp))
            { valTab[j]=1;
                X=X+p;
            }
            else
            {
                valTab[j+1]=1;
                goto end;
            }

        }
        lastp=p;
        p=1;
    }
end:
//    PRINTTAB(valTab, SIZE, fx->e);


    fx->val=0;
    //printf("%d\n", j+1);
    for(int i = j+1; i<SIZE; i++)
    {
        a=i;
        POW(valTab[a],a-j-1);
        fx->val+=valTab[i];
    }

//    int* fxtab = fixedPointtoTab(*fx);
//    PRINTTAB(fxtab,fx->e+fx->v+1,fx->e);


    return true;
}

int* fixedPointtoTab(FixedPoint x)
{
    int* tab = calloc(SIZE,sizeof(int));
    int realsize = x.e+x.v+1;
    for(int i = 0; i<realsize; i++)
    {
        tab[i]=x.val%2;
        x.val/=2;
    }
    return tab;
}

#define max(a,b) (a>b ? a : b)
FixedPoint PLUS(FixedPoint x1, FixedPoint x2)
{
    FixedPoint result;
    int re, rv;
    re=max(x1.e, x2.e);
    rv=max(x1.v, x2.v);

    int p=1;
    if(rv==x1.v)
    {
        POW(p,rv-x2.v);
        x2.val*=p;
        x2.v=rv;
    }
    else
    {
        POW(p,rv-x1.v);
        x1.val*=p;
        x1.v=rv;
    }

    //p is the sign bit

    if(re==x1.e)
    {
        if(x2.val>>(rv+x2.e))
            for(int i=1,p=1; i<=re-x2.e; i++, p=1)
            {
                p=p<<(rv+x2.e+i);
                //printf("p=%d\n", p);
                x2.val+=p;
            }
        x2.e=re;
    }
    else
    {
        if(x1.val>>(rv+x1.e))
            for(int i=1,p=1; i<=re-x1.e; i++, p=1)
            {
                p=p<<(rv+x1.e+i);
                x1.val+=p;
            }
        x1.e=re;
    }

    re++;
    result.val=x1.val+x2.val;

    while(!initFixedPoint(&result,re,rv))
    {
        rv--;
        result.val=result.val>>1; // troncature
    }

    int* resulttab =fixedPointtoTab(result);
    int* x1tab = fixedPointtoTab(x1);
    int* x2tab = fixedPointtoTab(x2);
    printf(" ");
    PRINTTAB(x1tab,x1.e+x1.v+1, x1.e);
    printf("+");
    PRINTTAB(x2tab,x2.e+x2.v+1, x2.e);
    printf("-------------------------\n=");
    PRINTTAB(resulttab, result.e+result.v+1, result.e);

    return result;

}


FixedPoint MULT(FixedPoint x1, FixedPoint x2)
{
    FixedPoint result;
    result.val=x1.val * x2.val;
    int rv = x1.v+x2.v;
    while(!initFixedPoint(&result, x1.e+x2.e, rv))
    {
        rv--;
        result.val=result.val>>1;
    }
    return result;
}
