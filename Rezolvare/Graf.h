#ifndef GRAF_H
#define GRAF_H

#include "General.h"
#include "Coada.h"

Graf *CreareGraf();
void AdaugareGraf(Graf *g,int varf1,int varf2);
Graf *StergereGraf(Graf *g);
int VerificareGradIntrare(Graf *g,int varf);
int VerificareGradIesire(Graf *g,int varf);
void GasireTrasee(Graf *g,int varf,FILE **fisier,int *nrDrum,int lungimeDrum,int *drum);

#endif