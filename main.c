#include <stdio.h>
#include "integration.h"


int main() {

	DaneWejscioweCalkowania daneWejsciowe = pobierzDane();

	double wynikMetodyProstokatow = obliczMetodaProstokatow(daneWejsciowe);
	double wynikMetodyTrapezow = obliczMetodaTrapezow(daneWejsciowe);
	double wynikMetodyMonteCarlo = obliczMetodaMonteCarlo(daneWejsciowe);

	// Prezentacja wyników w konsoli.
	wyswietlRaport(daneWejsciowe, wynikMetodyProstokatow, wynikMetodyTrapezow, wynikMetodyMonteCarlo);

	// Zapis wyników do pliku
	zapiszWynikiDoPliku(daneWejsciowe, wynikMetodyProstokatow, wynikMetodyTrapezow, wynikMetodyMonteCarlo);
	

	return 0;
}
