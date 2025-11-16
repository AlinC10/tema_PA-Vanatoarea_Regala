#include "Heap.h"

Heap *CreareHeap()
{
    Heap *h=malloc(sizeof(Heap));
    if(h==NULL)
    {
        printf("Nu s-a putut aloca spatiu");
        exit(1);
    }
    h->capacitate=8;
    h->nrParticipanti=0;
    h->participanti=calloc(h->capacitate,sizeof(Vanatoare));
    if(h->participanti==NULL)
    {
        printf("Nu s-a putut aloca spatiu");
        exit(1);
    }
    return h;
}

Informatii ValoareMaxima(BST **radacina)
{
    BST *nod=*radacina;
    while(nod->drp!=NULL)
        nod=nod->drp;
    Informatii aux=CopieProfunda(nod->participant);
    *radacina=StergereNodBST(*radacina,nod->participant);
    return aux;
}

void Adaugare(Vanatoare *deInlocuit,Vanatoare *inlocuitor,int ok)
{
    if(ok)
    {
        if(deInlocuit->participant.nume)
            EliberareMemorieNume(&deInlocuit->participant.nume);
        if(deInlocuit->paduri)
            EliberareMemorieNume(&inlocuitor->paduri);
    }
    deInlocuit->participant=CopieProfunda(inlocuitor->participant);
    strcpy(deInlocuit->traseu,inlocuitor->traseu);
    deInlocuit->paduri=strdup(inlocuitor->paduri);
    if(inlocuitor->participant.nume)
        EliberareMemorieNume(&inlocuitor->participant.nume);
    if(inlocuitor->paduri)
        EliberareMemorieNume(&inlocuitor->paduri);
}

void CernereInSus(Heap *h,Vanatoare detalii,int i)
{
    int ok=1;
    if(h->participanti[i].participant.nume && strcmp(h->participanti[i].participant.nume,detalii.participant.nume)==0)
        ok=0;
    while(i>0 && detalii.participant.experienta>h->participanti[(i-1)/2].participant.experienta)
    {
        Adaugare(&h->participanti[i],&h->participanti[(i-1)/2],ok);
        i=(i-1)/2;
    }
    Adaugare(&h->participanti[i],&detalii,ok);
}

void InserareHeap(Heap *h,Vanatoare detalii)
{
    h->nrParticipanti++;
    CernereInSus(h,detalii,h->nrParticipanti-1);
}

void AfisareRepartitieTrasee(Heap *h,FILE **fisier)
{
    fprintf(*fisier,"Nume_Traseu - Nume_Participant (Experienta_participant)");
    for(int i=0;i<h->capacitate;i++)
        fprintf(*fisier,"\n%s - %s (%.2f)",h->participanti[i].traseu,h->participanti[i].participant.nume,h->participanti[i].participant.experienta);
    fclose(*fisier);
}

void ExtragereParticipant(Heap *vanatoareaRegala,BST **arbore,FILE **trasee)
{
    Vanatoare detalii;
    char aux[100];
    detalii.participant=ValoareMaxima(arbore);
    fscanf(*trasee,"%2s:",detalii.traseu);
    fgets(aux,100,*trasee);
    detalii.paduri=strdup(aux);
    InserareHeap(vanatoareaRegala,detalii);
}

void UmplereHeap(BST **lorzi,BST **cavaleriAventurieri)
{
    FILE *trasee=DeschidereFisier("Pas_4/trasee.csv","rt");
    Heap *vanatoareaRegala=CreareHeap();
    Vanatoare detalii;
    char aux[100];
    char *p;
    while(vanatoareaRegala->nrParticipanti<vanatoareaRegala->capacitate)
    {
        ExtragereParticipant(vanatoareaRegala,lorzi,&trasee);
        ExtragereParticipant(vanatoareaRegala,cavaleriAventurieri,&trasee);
    }
    fclose(trasee);
    FILE *fisier=DeschidereFisier("Pas_4/test_4.csv","wt");
    AfisareRepartitieTrasee(vanatoareaRegala,&fisier);
    ModificareExperienta(vanatoareaRegala);
    fisier=DeschidereFisier("Pas_5/test_5.csv","wt");
    AfisareRepartitieTrasee(vanatoareaRegala,&fisier);
    AfisareTop3(vanatoareaRegala);
    vanatoareaRegala=StergereHeap(vanatoareaRegala);
}

Heap *StergereHeap(Heap *h)
{
    for(int i=0;i<h->capacitate;i++)
    {
        EliberareMemorieNume(&h->participanti[i].paduri);
        EliberareMemorieNume(&h->participanti[i].participant.nume);
    }
    free(h->participanti);
    h->participanti=NULL;
    free(h);
    h=NULL;
    return h;
}

void ModificareExperienta(Heap *h)
{
    for(int i=1;i<=h->nrParticipanti;i++)
    {
        int j=0;
        while(i!=h->participanti[j].traseu[1]-'0')
            j++;
        char *numere=strtok(h->participanti[j].paduri," ");
        h->participanti[j].participant.experienta+=atoi(numere);
        while(numere=strtok(NULL," "))
            h->participanti[j].participant.experienta+=atoi(numere);
        CernereInSus(h,h->participanti[j],j);
    }
}

void AfisareTop3(Heap *h)
{
    FILE *fisier=DeschidereFisier("Pas_6/test_6.csv","wt");
    fprintf(fisier,"Nume Experienta_totala");
    int i=0;
    while(h->nrParticipanti>5)
    {
        fprintf(fisier,"\n%s %.2f",h->participanti[0].participant.nume,h->participanti[0].participant.experienta);
        EliberareMemorieNume(&h->participanti[0].participant.nume);
        EliberareMemorieNume(&h->participanti[0].paduri);
        h->participanti[0]=CopieProfundaVanatoare(&h->participanti[h->nrParticipanti-1]);
        CernereInJos(h,0);
        h->nrParticipanti--;
    }    
    fclose(fisier);
}

int CopilStanga(Heap *h,int i)
{
    int poz=2*i+1;
    if(poz>h->nrParticipanti-1 || i<0)
        return -1;
    return poz;
}

int CopilDreapta(Heap *h,int i)
{
    int poz=2*i+2;
    if(poz>h->nrParticipanti-1 || i<0)
        return -1;
    return poz;
}

Vanatoare CopieProfundaVanatoare(Vanatoare *concurent)
{
    Vanatoare aux;
    aux.participant=CopieProfunda((*concurent).participant);
    aux.paduri=strdup((*concurent).paduri);
    strcpy(aux.traseu,concurent->traseu);
    EliberareMemorieNume(&concurent->participant.nume);
    EliberareMemorieNume(&concurent->paduri);
    return aux;
}

void CernereInJos(Heap *h,int i)
{
    int max=i,stg,drp;
    Vanatoare aux;
    stg=CopilStanga(h,i);
    drp=CopilDreapta(h,i);
    if(stg==-1 && drp==-1)
        return;
    if(stg!=-1 && h->participanti[stg].participant.experienta>h->participanti[max].participant.experienta)
        max=stg;
    if(drp!=-1 && h->participanti[drp].participant.experienta>h->participanti[max].participant.experienta)
        max=drp;
    if(max!=i)
    {
        aux=CopieProfundaVanatoare(&h->participanti[i]);
        h->participanti[i]=CopieProfundaVanatoare(&h->participanti[max]);
        h->participanti[max]=CopieProfundaVanatoare(&aux);
        CernereInJos(h,max);
    }
    return;
}
