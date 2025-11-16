#include "BST.h"
#include "Heap.h"


BST *CreareNodBST(Informatii participant)
{
    BST *nodNou=malloc(sizeof(BST));
    nodNou->drp=nodNou->stg=NULL;
    nodNou->participant=CopieProfunda(participant);
    return nodNou;
}

BST *AdaugareBST(BST *nod,Informatii participant)
{
    if(nod==NULL)
        return CreareNodBST(participant);
    if(participant.experienta>=nod->participant.experienta)
        nod->drp=AdaugareBST(nod->drp,participant);
    else
        nod->stg=AdaugareBST(nod->stg,participant);
    return nod;
}

void DRS(BST *nod,FILE **fisier)
{
    if(nod!=NULL)
    {
        DRS(nod->drp,fisier);
        fprintf(*fisier,"\n%s %.2f %d ",nod->participant.nume,nod->participant.experienta,nod->participant.varsta);
        switch(nod->participant.statutSocial)
        {
            case 1:
            {
                fprintf(*fisier,"LORD");
                break;
            }
            case 2:
            {
                fprintf(*fisier,"CAVALER");
                break;
            }
            case 3:
            {
                fprintf(*fisier,"AVENTURIER");
                break;
            }
        }
        DRS(nod->stg,fisier);
    }
}

void AfisareBST(BST *nod,FILE **fisier)
{ 
    fprintf(*fisier,"Nume Experienta Varsta Statut_social");
    DRS(nod,fisier);
    fclose(*fisier);
}

BST *NodValoareMinima(BST *nod)
{
    if(nod==NULL)
        return nod;
    while(nod->stg!=NULL)
        nod=nod->stg;
    return nod;
}

BST *StergereNodBST(BST *radacina,Informatii persoana)
{
    if(persoana.nume==NULL)
        return NULL;
    if(radacina==NULL)
      return radacina;
    if(radacina->participant.experienta>persoana.experienta)
        radacina->stg=StergereNodBST(radacina->stg,persoana);
    else if(radacina->participant.experienta<persoana.experienta  || (radacina->participant.experienta==persoana.experienta && strcmp(radacina->participant.nume,persoana.nume)))
        radacina->drp=StergereNodBST(radacina->drp,persoana);
    else if(radacina->participant.experienta==persoana.experienta && strcmp(radacina->participant.nume,persoana.nume)==0)
    {
        if(radacina->stg==NULL)
        {
            BST *aux=radacina;
            radacina=radacina->drp;
            EliberareMemorieNume(&(aux->participant).nume);
            free(aux);
            aux=NULL;
            return radacina;
        }
        else
        {
            if(radacina->drp==NULL)
            {
                BST *aux=radacina;
                radacina=radacina->stg;
                EliberareMemorieNume(&(aux->participant).nume);
                free(aux);
                aux=NULL;
                return radacina;
            }
        }
        BST *aux=NodValoareMinima(radacina->drp);
        EliberareMemorieNume(&radacina->participant.nume);
        radacina->participant=CopieProfunda(aux->participant);
        radacina->drp=StergereNodBST(radacina->drp,aux->participant);
    }
    return radacina;
}

BST *StergereBST(BST *radacina)
{
    while(radacina!=NULL)
        radacina=StergereNodBST(radacina,radacina->participant);
    return radacina;
}

void Pasul2(BST **lorzi,BST **cavaleriAventurieri)
{
    FILE *fisierLorzi=DeschidereFisier("Pas_2/test_2_lorzi.csv","wt");
    AfisareBST(*lorzi,&fisierLorzi);
    FILE *fisierCavaleriAventurieri=DeschidereFisier("Pas_2/test_2_cavaleri_aventurieri.csv","wt");
    AfisareBST(*cavaleriAventurieri,&fisierCavaleriAventurieri);
    fisierLorzi=DeschidereFisier("Pas_3/contestatii.csv","rt");
    char aux[100];
    fgets(aux,100,fisierLorzi);
    while(feof(fisierLorzi)==0)
    {
        Informatii lord=CitireInf(&fisierLorzi);
        *lorzi=StergereNodBST(*lorzi,lord);
        EliberareMemorieNume(&lord.nume);
    }
    fclose(fisierLorzi);
    fisierLorzi=DeschidereFisier("Pas_3/test_3_lorzi.csv","wt");
    AfisareBST(*lorzi,&fisierLorzi);
    UmplereHeap(lorzi,cavaleriAventurieri);
    *lorzi=StergereBST(*lorzi);
    *cavaleriAventurieri=StergereBST(*cavaleriAventurieri);
}