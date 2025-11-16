#ifndef GENERAL_H
#define GENERAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

enum statut {
    lord=1,cavaler,aventurier
};

typedef struct {
    char *nume;
    int varsta;
    float experienta;
    enum statut statutSocial;
}Informatii;

typedef struct nod {
    union tipDateNod{
        Informatii participant;
        int nr;
    }tipDate;
    struct nod *urm;
}Nod;

typedef struct {
    Nod *primul,*ultimul;
}Coada;

typedef struct bst {
    Informatii participant;
    struct bst *stg,*drp;
}BST;

typedef struct vanatoare {
    Informatii participant;
    char traseu[2];
    char *paduri;
}Vanatoare;

typedef struct heap {
    Vanatoare *participanti;
    int nrParticipanti,capacitate;
}Heap;

typedef struct {
    int v,m;
    Nod **vector;
}Graf;

FILE *DeschidereFisier(char numeFisier[], char modDeschidere[]);
void EliberareMemorieNume(char **nume);
Informatii CopieProfunda(Informatii participant);
char *TransfLitereMici(char cuv[]);
Informatii CitireInf(FILE **fisierInf);
void CitireNume(char aux[],FILE **fisierInf);

#endif
