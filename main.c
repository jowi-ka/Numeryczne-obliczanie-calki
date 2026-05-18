#include <stdio.h>
#include "integration.h"
#include "reports.h"
#include "ui_handler.h"
#include <time.h>
#include "config.h"

int main() {

	MetodaCalkowania metodyCalkowania[] = {
	obliczMetodaProstokatow,
	obliczMetodaTrapezow,
	obliczMetodaMonteCarlo
	};

	const char* nazwyMetod[LICZBA_METOD] = {
		"Metoda Prostokatow",
		"Metoda Trapezow",
		"Metoda Monte Carlo"
	};

	printf("~~~~ PROJEKT 20: NUMERYCZNE OBLICZANIE CALKI ~~~~\n\n");
	DaneWejscioweCalkowania daneWejsciowe;
	srand((unsigned int)time(NULL));
	wczytajDane(&daneWejsciowe);

	double wyniki[LICZBA_METOD];

	for (int i = 0; i < LICZBA_METOD; i++) {
		wyniki[i] = metodyCalkowania[i](&daneWejsciowe);
	}

	generujRaport(stdout, &daneWejsciowe, wyniki, nazwyMetod, LICZBA_METOD);
	zapiszWynikiDoPliku(&daneWejsciowe, wyniki, nazwyMetod, LICZBA_METOD);

	return 0;
}