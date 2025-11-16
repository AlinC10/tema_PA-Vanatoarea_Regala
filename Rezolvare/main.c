#include "Coada.h"
#include "General.h"
#include "BST.h"
#include "Heap.h"
#include "Graf.h"

int main() 
{
	Pasul1();
	Graf *paduri=CreareGraf();
	FILE *iesirePas7=DeschidereFisier("Pas_7/test_7.csv","wt");
	int nrDrum=1;
	int *drum=calloc(paduri->v,sizeof(int));
	for(int j=0;j<paduri->v;j++)
	{
		if(VerificareGradIntrare(paduri,j))
		{
			Nod *aux=paduri->vector[j]->urm;
			int lungimeDrum=0;
			GasireTrasee(paduri,j,&iesirePas7,&nrDrum,lungimeDrum,drum);
		}
	}
	fclose(iesirePas7);
	paduri=StergereGraf(paduri);
	free(drum);
	drum=NULL;
	return 0;
}