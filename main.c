#include <stdio.h>
#include "integration.h"
#include "reports.h"
#include "ui_handler.h"


int main() {
	const char* nazwyMetod[LICZBA_METOD] = {
		"Metoda Prostokatow",
		"Metoda Trapezow",
		"Metoda Monte Carlo"
	};

	printf("~~~~ PROJEKT 20: NUMERYCZNE OBLICZANIE CALKI ~~~~\n\n");
	DaneWejscioweCalkowania daneWejsciowe;
	wczytajDane(&daneWejsciowe);


	double wyniki[LICZBA_METOD];
	wyniki[0] = obliczMetodaProstokatow(daneWejsciowe);
	wyniki[1] = obliczMetodaTrapezow(daneWejsciowe);
	wyniki[2] = obliczMetodaMonteCarlo(daneWejsciowe);

	generujRaport(stdout, &daneWejsciowe, wyniki, nazwyMetod, LICZBA_METOD);
	zapiszWynikiDoPliku(&daneWejsciowe, wyniki, nazwyMetod, LICZBA_METOD);

	return 0;
}