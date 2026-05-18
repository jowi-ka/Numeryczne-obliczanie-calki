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

static void uruchomObliczeniaCalkowania(const DefinicjaMetody* metody, int liczbaMetod, 
										const DaneWejscioweCalkowania* dane, double* tablicaWynikow, const char** tablicaNazw) {
	for (int i = 0; i < liczbaMetod; i++) {
		tablicaWynikow[i] = metody[i].funkcja(dane);
		tablicaNazw[i] = metody[i].nazwa;
	}
}

int main() {
	DaneWejscioweCalkowania daneWejsciowe;
	srand((unsigned int)time(NULL));
	DefinicjaMetody metodyCalkowania[] = {
		{"Metoda Prostokatow", obliczMetodaProstokatow},
		{"Metoda Trapezow",    obliczMetodaTrapezow},
		{"Metoda Monte Carlo", obliczMetodaMonteCarlo}
	};
	double* wyniki = bezpiecznyMalloc(LICZBA_METOD * sizeof(double), "tablica wynikow");
	const char** nazwyMetod = bezpiecznyMalloc(LICZBA_METOD * sizeof(char*), "nazwy metod");
	printf("~~~~ PROJEKT 20: NUMERYCZNE OBLICZANIE CALKI ~~~~\n\n");
	wczytajDane(&daneWejsciowe);
	
	uruchomObliczeniaCalkowania(metodyCalkowania, LICZBA_METOD, &daneWejsciowe, wyniki, nazwyMetod);
	
	generujRaport(stdout, &daneWejsciowe, wyniki, nazwyMetod, LICZBA_METOD);
	zapiszWynikiDoPliku(&daneWejsciowe, wyniki, nazwyMetod, LICZBA_METOD);

	free(wyniki);
	free(nazwyMetod);
	
	return 0;
}