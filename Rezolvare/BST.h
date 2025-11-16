#ifndef BST_H
#define BST_H

#include "General.h"
#include "Heap.h"

BST *CreareNodBST(Informatii participant);
BST *AdaugareBST(BST *nod,Informatii participant);
void DRS(BST *nod,FILE **fisier);
void AfisareBST(BST *nod,FILE **fisier);
BST *StergereBST(BST *radacina);
void Pasul2(BST **lorzi,BST **cavaleriAventurieri);
BST *NodValoareMinima(BST *nod);
BST *StergereNodBST(BST *radacina,Informatii persoana);

#endif