#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "integration.h"

int main() {
	double poczatekPrzedzialu, koniecPrzedzialu, zadanaDokladnosc;

	int wyborUzytkownika, liczbaPodprzedzialow;

	double wynikMetodyProstokatow, wynikMetodyTrapezow, wynikMetodyMonteCarlo;

	printf("~~~~ Projekt 20: Numeryczne obliczanie całki ~~~~\n");

	printf("Podaj początek przedziału: ");
	scanf(" %lf", &poczatekPrzedzialu);

	printf("Podaj koniec przedzialu: ");
	scanf("%lf", &koniecPrzedzialu);

	printf("\n~~~~ Dostepne warianty obliczen ~~~~\n");
	printf("1. Obliczenia dla zadanej liczby podprzedzialow (n)\n");
	printf("2. Obliczenia dla zadanej dokladnosci \n");
	printf("Wybierz opcje: ");
	scanf("%d", &wyborUzytkownika);

	if (wyborUzytkownika == 1) {
		// Wariant A: Liczba podprzedziałów
		printf("Podaj liczbę przedziałów: ");
		scanf("%d", &liczbaPodprzedzialow);

	} else if (wyborUzytkownika == 2) {
		// Wariant B: Dokladnosc
		printf("Podaj wymagana dokladnosc: ");
		scanf("%lf", &zadanaDokladnosc);
		liczbaPodprzedzialow = (int)(1.0 / zadanaDokladnosc);	

	} else {
	printf("Blad: Nieprawidlowy wybor wariantu.\n");
	return 1; 
	}

	wynikMetodyProstokatow = obliczMetodaProstokatow(poczatekPrzedzialu, koniecPrzedzialu, liczbaPodprzedzialow);
	wynikMetodyTrapezow = obliczMetodaTrapezow(poczatekPrzedzialu, koniecPrzedzialu, liczbaPodprzedzialow);
	wynikMetodyMonteCarlo = obliczMetodaMonteCarlo(poczatekPrzedzialu, koniecPrzedzialu, liczbaPodprzedzialow);

	printf("Wyniki dla n = %d", liczbaPodprzedzialow);
	printf("Metoda Prostokatow: %.10f\n", wynikMetodyProstokatow);
	printf("Metoda Trapezow:    %.10f\n", wynikMetodyTrapezow);
	printf("Metoda Monte Carlo: %.10f\n", wynikMetodyMonteCarlo);

	FILE* plik = fopen("wyniki.txt", "w");
	if (plik != NULL) {
		fprintf(plik, "Wyniki dla przedzialu [%.2f, %.2f]\n", poczatekPrzedzialu, koniecPrzedzialu);
		fprintf(plik, "Liczba podprzedzialow: %d\n\n", liczbaPodprzedzialow);
		fprintf(plik, "Metoda Prostokatow: %f\n", wynikMetodyProstokatow);
		fprintf(plik, "Metoda Trapezow:    %f\n", wynikMetodyTrapezow);
		fprintf(plik, "Metoda Monte Carlo: %f\n", wynikMetodyMonteCarlo);
		fclose(plik);
		printf("\nWyniki zostaly zapisane do pliku wyniki.txt\n");
	}
	

	return 0;
}
