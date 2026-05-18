#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "integration.h"
#include "reports.h"
#include "ui_handler.h"
#include "config.h"
#include "mem_utils.h"

typedef struct {
	const char* nazwa;
	MetodaCalkowania funkcja;
} DefinicjaMetody;

int main() {

	DefinicjaMetody metodyCalkowania[] = {
		{"Metoda Prostokatow", obliczMetodaProstokatow},
		{"Metoda Trapezow",    obliczMetodaTrapezow},
		{"Metoda Monte Carlo", obliczMetodaMonteCarlo}
	};

	printf("~~~~ PROJEKT 20: NUMERYCZNE OBLICZANIE CALKI ~~~~\n\n");
	DaneWejscioweCalkowania daneWejsciowe;
	srand((unsigned int)time(NULL));

	wczytajDane(&daneWejsciowe);
	
	double* wyniki = bezpiecznyMalloc(LICZBA_METOD * sizeof(double), "tablica wynikow");
	const char** nazwyMetod = bezpiecznyMalloc(LICZBA_METOD * sizeof(char*), "nazwy metod");

	for (int i = 0; i < LICZBA_METOD; i++) {
		wyniki[i] = metodyCalkowania[i].funkcja(&daneWejsciowe);
		nazwyMetod[i] = metodyCalkowania[i].nazwa;
	}
	
	generujRaport(stdout, &daneWejsciowe, wyniki, nazwyMetod, LICZBA_METOD);
	zapiszWynikiDoPliku(&daneWejsciowe, wyniki, nazwyMetod, LICZBA_METOD);

	free(wyniki);
	free(nazwyMetod);
	
	return 0;
}