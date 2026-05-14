#include <stdio.h>
#include "integration.h"
#include "reports.h"
#include "ui_handler.h"


int main() {
	const char* nazwyMetod[] = {
		"Metoda Prostokatow",
		"Metoda Trapezow",
		"Metoda Monte Carlo"
	};

	printf("~~~~ PROJEKT 20: NUMERYCZNE OBLICZANIE CALKI ~~~~\n\n");
	DaneWejscioweCalkowania daneWejsciowe;
	wczytajDane(&daneWejsciowe);


	double wyniki[3];
	wyniki[0] = obliczMetodaProstokatow(daneWejsciowe);
	wyniki[1] = obliczMetodaTrapezow(daneWejsciowe);
	wyniki[2] = obliczMetodaMonteCarlo(daneWejsciowe);

	generujRaport(stdout, &daneWejsciowe, wyniki, nazwyMetod, 3);
	zapiszWynikiDoPliku(&daneWejsciowe, wyniki, nazwyMetod, 3);

	return 0;
}