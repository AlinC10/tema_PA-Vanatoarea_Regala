#ifndef HEAP_H
#define HEAP_H

#include "General.h"
#include "BST.h"

Heap *CreareHeap();
Informatii ValoareMaxima(BST **radacina);
void CernereInSus(Heap *h,Vanatoare detalii,int i);
void InserareHeap(Heap *h,Vanatoare detalii);
void AfisareRepartitieTrasee(Heap *h,FILE **fisier);
void UmplereHeap(BST **lorzi,BST **cavaleriAventurieri);
Heap *StergereHeap(Heap *h);
void ModificareExperienta(Heap *h);
void AfisareTop3(Heap *h);
void Adaugare(Vanatoare *deInlocuit,Vanatoare *inlocuitor,int ok);
void ExtragereParticipant(Heap *vanatoareaRegala,BST **arbore,FILE **trasee);
//
int CopilStanga(Heap *h,int i);
int CopilDreapta(Heap *h,int i);
Vanatoare CopieProfundaVanatoare(Vanatoare *concurent);
void CernereInJos(Heap *h,int i);

#endif