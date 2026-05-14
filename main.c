#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "integration.h"

DaneWejscioweCalkowania pobierzDane() {
	
	// Deklaracja zmiennych
	DaneWejscioweCalkowania dane;
	int wyborWariantu;
	double zadanaDokladnosc;

	// Interfejs użytkownika wraz z pobraniem danych wejściowych
	printf("~~~~ PROJEKT 20: NUMERYCZNE OBLICZANIE CALKI ~~~~\n");

	printf("Podaj poczatek przedzialu: \n");
	scanf(" %lf", &dane.poczatekPrzedzialu);

	printf("Podaj koniec przedzialu: ");
	scanf(" %lf", &dane.koniecPrzedzialu);

	printf("\n~~~~ Dostepne warianty obliczen ~~~~\n");
	printf("1. Obliczenia dla zadanej liczby podprzedzialow (n)\n");
	printf("2. Obliczenia dla zadanej dokladnosci \n");
	printf("Wybierz opcje: ");
	scanf(" %d", &wyborWariantu);

	if (wyborWariantu == 1) {
		// Wariant A: Obliczanie na podstawie wprowadzonej przez użytkownika liczby podprzedziałów
		printf("Podaj liczbę podprzedzialow: ");
		scanf(" %d", &dane.liczbaPodprzedzialow);

	}
	else if (wyborWariantu == 2) {
		// Wariant B: Obliczanie na podstawie wprowadzonej przez użytkownika dokładności
		printf("Podaj wymagana dokladnosc: ");
		scanf(" %lf", &zadanaDokladnosc);
		dane.liczbaPodprzedzialow = (int)(1.0 / zadanaDokladnosc); // Uproszczone wyznaczanie podprzedziałów

	}
	else {
		printf("Blad: Nieprawidlowy wybor wariantu.\n");
	}

	return dane;
}

void wyswietlRaport(DaneWejscioweCalkowania dane, double wynikMetodyProstokatow, double wynikMetodyTrapezow, double wynikMetodyMonteCarlo) {
	printf("Wyniki dla n = %d\n", dane.liczbaPodprzedzialow);
	printf("Metoda Prostokatow: %.10f\n", wynikMetodyProstokatow);
	printf("Metoda Trapezow:    %.10f\n", wynikMetodyTrapezow);
	printf("Metoda Monte Carlo: %.10f\n", wynikMetodyMonteCarlo);
}

void zapiszWynikiDoPliku(DaneWejscioweCalkowania dane, double wynikMetodyProstokatow, double wynikMetodyTrapezow, double wynikMetodyMonteCarlo) {
	FILE* plik = fopen("wyniki.txt", "w");
	if (plik != NULL) {
		fprintf(plik, "Wyniki dla przedzialu [%.2f, %.2f]\n", dane.poczatekPrzedzialu, dane.koniecPrzedzialu);
		fprintf(plik, "Liczba podprzedzialow: %d\n\n", dane.liczbaPodprzedzialow);
		fprintf(plik, "Metoda Prostokatow: %f\n", wynikMetodyProstokatow);
		fprintf(plik, "Metoda Trapezow:    %f\n", wynikMetodyTrapezow);
		fprintf(plik, "Metoda Monte Carlo: %f\n", wynikMetodyMonteCarlo);
		fclose(plik);
		printf("\nWyniki zostaly zapisane do pliku wyniki.txt\n");
	}
}


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
