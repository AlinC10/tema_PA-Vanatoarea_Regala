#include "General.h"

FILE *DeschidereFisier(char numeFisier[], char modDeschidere[])
{
    FILE *fisier;
    if((fisier=fopen(numeFisier,modDeschidere))==NULL)
    {
        printf("Fisierul %s nu a putut fi deschis",numeFisier);
        exit(1);
    }
    return fisier;
}

void EliberareMemorieNume(char **nume)
{
    if(*nume)
    {
        free(*nume);
        *nume=NULL;
    }
}

Informatii CopieProfunda(Informatii participant)
{
    Informatii aux;
    aux.nume=strdup(participant.nume);
    aux.experienta=participant.experienta;
    aux.varsta=participant.varsta;
    aux.statutSocial=participant.statutSocial;
    return aux;
}

char *TransfLitereMici(char cuv[])
{
    for(int i=0;i<strlen(cuv);i++)
        if(islower(cuv[i])==0)
            cuv[i]=tolower(cuv[i]);
    return cuv;
}

Informatii CitireInf(FILE **fisierInf)
{
    Informatii participant;
    char aux[100];
    char c;
    fscanf(*fisierInf,"%s ",aux);
    if(strcmp("lord",TransfLitereMici(aux))==0)
        participant.statutSocial=lord;
    else if(strcmp("cavaler",TransfLitereMici(aux))==0)
        participant.statutSocial=cavaler;
        else if(strcmp("aventurier",TransfLitereMici(aux))==0)
            participant.statutSocial=aventurier;
    aux[0]='\0';
    CitireNume(aux,fisierInf);
    participant.nume=malloc(strlen(aux)+1);
    strcpy(participant.nume,aux);
    fscanf(*fisierInf,"%f;%d ",&participant.experienta,&participant.varsta);
    return participant;
}

void CitireNume(char aux[],FILE **fisierInf)
{
    char c;
    int i=-1;
    do
    {
        i++;
        c=getc(*fisierInf);
        if(c==';')
            break;
        if(i==0 || (aux[i-1]=='-' && i!=0))
            aux[i]=toupper(c);
        else
            aux[i]=tolower(c);
        if(c==' ')
            aux[i]='-';
    }while(c!=';');
    aux[i]='\0';
}