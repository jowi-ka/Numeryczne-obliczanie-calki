#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "integration.h"

void zamienLiczby(double* a, double* b);
void wyczyscBufor();
void walidujGranice(DaneWejscioweCalkowania* dane);
void wczytajWariantObliczen(DaneWejscioweCalkowania* dane);


void wyczyscBufor() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

void zamienLiczby(double* a, double* b) {
	double temp = *a;
	*a = *b;
	*b = temp;
}

double pobierzLiczbe(const char* komunikat) {
	double wartosc;
	while (1) {
		printf("%s", komunikat);
		if (scanf("%lf", &wartosc) == 1) {
			return wartosc;
		}
		printf("Blad: To nie jest liczba!\n");
		wyczyscBufor();
	}
}

int obsluzBladGranic(DaneWejscioweCalkowania* dane) {
	int decyzja;
	printf("\nBlad! Poczatek przedzialu (%.2f) jest wiekszy niz koniec (%.2f)\n",
		dane->poczatekPrzedzialu, dane->koniecPrzedzialu);

	while (1) {
		printf("\nCo chcesz zrobić?\n");
		printf("[1] Zamien automatycznie granice miejscami\n[2] Wpisz granice ponownie\n");
		printf("Twoj wybor: ");

		if (scanf("%d", &decyzja) != 1) {
			printf("Blad: To nie jest liczba!\n");
			wyczyscBufor();
			continue;
		}

		if (decyzja == 1) {
			zamienLiczby(&dane->poczatekPrzedzialu, &dane->koniecPrzedzialu);
			return 1; // Naprawione (sukces)
		}
		else if (decyzja == 2) {
			return 0; // Wpisz ponownie (brak sukcesu)
		}
		printf("Blad: Wybierz 1 lub 2.\n");
	}
}

void wczytajGranice(DaneWejscioweCalkowania* dane) {
	int sukces = 0;
	while (!sukces) {
		dane->poczatekPrzedzialu = pobierzLiczbe("\nPodaj poczatek przedzialu: ");
		dane->koniecPrzedzialu = pobierzLiczbe("Podaj koniec przedzialu: ");

		if (dane->poczatekPrzedzialu > dane->koniecPrzedzialu) {
			sukces = obsluzBladGranic(dane);
		}
		else {
			sukces = 1;
		}

		if (sukces) {
			printf("\nWYBRANE GRANICE PRZEDZIAŁU TO: [%.2f, %.2f]\n",
				dane->poczatekPrzedzialu, dane->koniecPrzedzialu);
		}
	}
}


void wczytajWariantObliczen(DaneWejscioweCalkowania* dane) {
	int wariant;
	double dokladnosc;

	printf("\n~~~~ Dostepne warianty obliczen ~~~~\n");
	printf("1. Obliczenia dla zadanej liczby podprzedzialow (n)\n");
	printf("2. Obliczenia dla zadanej dokladnosci \n");
	printf("Wybierz opcje: ");
	scanf(" %d", &wariant);

	if (wariant == 1) {
		// Wariant A: Obliczanie na podstawie wprowadzonej przez użytkownika liczby podprzedziałów
		printf("Podaj dodatnią liczbę podprzedzialow: ");
		scanf(" %d", &dane->liczbaPodprzedzialow);

	}
	else if (wariant == 2) {
		// Wariant B: Obliczanie na podstawie wprowadzonej przez użytkownika dokładności
		printf("Podaj wymagana dokladnosc: ");
		scanf(" %lf", &dokladnosc);
		dane->liczbaPodprzedzialow = (int)(1.0 / dokladnosc); // Uproszczone wyznaczanie podprzedziałów

	}
	else {
		printf("Blad: Nieprawidlowy wybor wariantu.\n");
	}
}


DaneWejscioweCalkowania wczytajDane() {

	// Deklaracja zmiennych
	DaneWejscioweCalkowania dane;
	// Pobranie granic przedziałów
	wczytajGranice(&dane);
	wczytajWariantObliczen(&dane);

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