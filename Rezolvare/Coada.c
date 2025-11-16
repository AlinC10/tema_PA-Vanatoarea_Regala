#include "Coada.h"

Coada *CreareCoada()
{
    Coada *q;
    q=malloc(sizeof(Coada));
    if(q==NULL)
    {
        printf("Coada nu a putut fi creata");
        exit(1);
    }
    q->primul=q->ultimul=NULL;
    return q;
}

Nod *CreareNod()
{
    Nod *nodNou=malloc(sizeof(Nod));
    if(nodNou==NULL)
    {
        printf("Nodul nu a putut fi creat");
        exit(1);
    }
    nodNou->urm=NULL;
    return nodNou;
}

void AdaugareCoada(Coada *date,Informatii participant)
{
    Nod *nodNou=CreareNod();
    (nodNou->tipDate.participant).nume=NULL;
    nodNou->tipDate.participant=CopieProfunda(participant);
    if(date->ultimul==NULL)
        date->ultimul=nodNou;
    else
    {
        (date->ultimul)->urm=nodNou;
        date->ultimul=nodNou;
    }
    if(date->primul==NULL)
        date->primul=date->ultimul;
}

int CoadaGoala(Coada *date)
{
    return (date->primul==NULL);
}

Informatii ScoatereCoada(Coada *date)
{
    if(CoadaGoala(date))
        printf("Coada este goala");
    Nod *aux=date->primul;
    Informatii participant=CopieProfunda(aux->tipDate.participant);
    date->primul=aux->urm;
    EliberareMemorieNume(&(aux->tipDate.participant).nume);
    free(aux);
    aux=NULL;
    if(date->primul==NULL)
        date->ultimul=NULL;
    return participant;
}

void StergereCoada(Coada **date,FILE **fisierInf)
{
    if(*date==NULL)
        return;
    free(*date);
    *date=NULL;
}

void AfisareCoada(Coada *date,FILE **fisierInf,BST **lorzi,BST **cavaleriAventurieri)
{
    fprintf(*fisierInf,"Nume Experienta Varsta Statut_social");
    Nod *aux=NULL;
    if(date==NULL)
        return;
    while(!CoadaGoala(date))
    {
        fprintf(*fisierInf,"\n");
        Informatii participant=ScoatereCoada(date);
        fprintf(*fisierInf,"%s %.2f %d ",participant.nume,participant.experienta,participant.varsta);
        switch(participant.statutSocial)
        {
            case 1:
            {
                fprintf(*fisierInf,"LORD");
                *lorzi=AdaugareBST(*lorzi,participant);
                break;
            }
            case 2:
            {
                fprintf(*fisierInf,"CAVALER");
                *cavaleriAventurieri=AdaugareBST(*cavaleriAventurieri,participant);
                break;
            }
            case 3:
            {
                fprintf(*fisierInf,"AVENTURIER");
                *cavaleriAventurieri=AdaugareBST(*cavaleriAventurieri,participant);
                break;
            }
        }
        EliberareMemorieNume(&participant.nume);
    }
}

void Pasul1()
{
    Coada *date=CreareCoada();
    BST *lorzi=NULL,*cavaleriAventurieri=NULL;
    FILE *fisierInf=DeschidereFisier("Pas_1/candidati.csv","rt");
    Informatii participant;
    char aux[100];
    fgets(aux,100,fisierInf);
    aux[0]='\0';
    while(!feof(fisierInf))
    {
        participant=CitireInf(&fisierInf);
        AdaugareCoada(date,participant);
        EliberareMemorieNume(&participant.nume);
    }
    fclose(fisierInf);
    fisierInf=DeschidereFisier("Pas_1/test_1.csv","wt");
    AfisareCoada(date,&fisierInf,&lorzi,&cavaleriAventurieri);
    fclose(fisierInf);
    StergereCoada(&date,&fisierInf);
    Pasul2(&lorzi,&cavaleriAventurieri);
} 