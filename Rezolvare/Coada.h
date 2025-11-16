#ifndef COADA_H
#define COADA_H

#include "General.h"
#include "BST.h"

Coada *CreareCoada();
Nod *CreareNod();
void AdaugareCoada(Coada *date,Informatii participant);
int CoadaGoala(Coada *date);
Informatii ScoatereCoada(Coada *date);
void StergereCoada(Coada **date,FILE **fisierInf);
void AfisareCoada(Coada *date,FILE **fisierInf,BST **lorzi,BST **cavaleriAventurieri);
void Pasul1();

#endif