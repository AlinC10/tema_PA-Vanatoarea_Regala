#include "Graf.h"

Graf *CreareGraf()
{
    int varf1,varf2;
    Graf *g=malloc(sizeof(Graf));
    if(g==NULL)
    {
        printf("Graful nu a fost creat");
        exit(1);
    }
    g->v=11;
    g->vector=calloc(g->v,sizeof(Nod*));
    if(g->vector==NULL)
    {
        printf("Lista de adiacenta nu a fost creata");
        free(g);
        exit(1);
    }
    for(int i=0;i<g->v;i++)
    {
        Nod *nodNou=CreareNod();
        nodNou->tipDate.nr=i;
        g->vector[i]=nodNou;
    }
    g->m=0;
    FILE *fisierMuchii=DeschidereFisier("Pas_7/drumuri.csv","rt");
    while(!feof(fisierMuchii))
    {
        fscanf(fisierMuchii,"%d%d\n",&varf1,&varf2);
        AdaugareGraf(g,varf1,varf2);
    }
    fclose(fisierMuchii);
    return g;
}

void AdaugareGraf(Graf *g,int varf1,int varf2)
{
    Nod *aux=g->vector[varf1];
    while(aux->urm && varf2>aux->urm->tipDate.nr)
        aux=aux->urm;
    Nod *nodNou=CreareNod();
    nodNou->tipDate.nr=varf2;
    nodNou->urm=aux->urm;
    aux->urm=nodNou;
    g->m++;
}

Graf *StergereGraf(Graf *g)
{
    for(int i=0;i<g->v;i++)
    {
        Nod *aux=g->vector[i];
        Nod *nodSters;
        while(aux)
        {
            nodSters=aux;
            aux=aux->urm;
            free(nodSters);
        }
    }
    free(g->vector);
    free(g);
    g=NULL;
    return g;
}

int VerificareGradIntrare(Graf *g,int varf)
{
    int exista=0;
    for(int i=0;i<g->v;i++)
    {
        if(i==varf)
            continue;
        Nod *aux=g->vector[i]->urm;
        while(aux)
        {
            if(aux->tipDate.nr==varf)
                return 0;
            aux=aux->urm;
        }
    }
    return 1;
}

int VerificareGradIesire(Graf *g,int varf)
{
    return g->vector[varf]->urm==NULL;
}

void GasireTrasee(Graf *g,int varf,FILE **fisier,int *nrDrum,int lungimeDrum,int *drum)
{
    drum[lungimeDrum]=varf;
    Nod *aux=g->vector[varf]->urm;
    while(aux)
    {
        GasireTrasee(g,aux->tipDate.nr,fisier,nrDrum,lungimeDrum+1,drum);
        aux=aux->urm;
    }
    if(VerificareGradIesire(g,varf))
    {
        if(*nrDrum!=1)
            fprintf(*fisier,"\n");
        fprintf(*fisier,"T%d:",*nrDrum);
        for(int i=0;i<=lungimeDrum;i++)
            fprintf(*fisier," %d",drum[i]);
        (*nrDrum)++;
    }
    drum[lungimeDrum]=0;        
}