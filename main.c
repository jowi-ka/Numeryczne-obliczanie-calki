#include <stdio.h>
#include "integration.h"


int main() {

	printf("~~~~ PROJEKT 20: NUMERYCZNE OBLICZANIE CALKI ~~~~\n\n");
	DaneWejscioweCalkowania daneWejsciowe = wczytajDane();

	double wynikMetodyProstokatow = obliczMetodaProstokatow(daneWejsciowe);
	double wynikMetodyTrapezow = obliczMetodaTrapezow(daneWejsciowe);
	double wynikMetodyMonteCarlo = obliczMetodaMonteCarlo(daneWejsciowe);

	// Prezentacja wyników w konsoli.
	wyswietlRaport(daneWejsciowe, wynikMetodyProstokatow, wynikMetodyTrapezow, wynikMetodyMonteCarlo);

	// Zapis wyników do pliku
	zapiszWynikiDoPliku(daneWejsciowe, wynikMetodyProstokatow, wynikMetodyTrapezow, wynikMetodyMonteCarlo);
	

	return 0;
}
