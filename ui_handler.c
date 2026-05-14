#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "integration.h"

// --- Prototypy funkcji pomocniczych ---
void zamienLiczby(double* a, double* b);
void wyczyscBufor();
double pobierzDouble(const char* komunikat);
double pobierzDodatniDouble(const char* komunikat);
int pobierzInt(const char* komunikat);
int pobierzDodatniInt(const char* komunikat);
int pobierzDecyzjeUzytkownika();

// --- Prototypy funkcji logicznych i wejścia/wyjścia ---
DaneWejscioweCalkowania wczytajDane();
int obsluzBladGranic(DaneWejscioweCalkowania* dane);
void wczytajGranice(DaneWejscioweCalkowania* dane);
void wczytajWariantObliczen(DaneWejscioweCalkowania* dane);
void wyswietlRaport(DaneWejscioweCalkowania dane, double wynikMetodyProstokatow, double wynikMetodyTrapezow, double wynikMetodyMonteCarlo);
void zapiszWynikiDoPliku(DaneWejscioweCalkowania dane, double wynikMetodyProstokatow, double wynikMetodyTrapezow, double wynikMetodyMonteCarlo);

void wyczyscBufor() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

void zamienLiczby(double* a, double* b) {
	double temp = *a;
	*a = *b;
	*b = temp;
}

double pobierzDouble(const char* komunikat) {
	double wartosc;
	while (1) {
		printf("%s", komunikat);
		if (scanf("%lf", &wartosc) == 1) {
			wyczyscBufor();
			return wartosc;
		}
		printf("Blad: To nie jest liczba!\n");
		wyczyscBufor();
	}
}
int pobierzInt(const char* komunikat) {
	int wartosc;
	while (1) {
		printf("%s", komunikat);
		if (scanf("%d", &wartosc) == 1) {
			wyczyscBufor();
			return wartosc;
		}
		printf("Blad: To nie jest liczba!\n");
		wyczyscBufor();
	}
}

int pobierzDodatniInt(const char* komunikat) {
	int wartosc;
	while (1) {
		wartosc = pobierzInt(komunikat);
		if (wartosc > 0) return wartosc;
		printf("Blad: Liczba musi byc wieksza od 0!\n");
	}
}

double pobierzDodatniDouble(const char* komunikat) {
	double wartosc;
	while (1) {
		wartosc = pobierzDouble(komunikat);
		if (wartosc > 0) return wartosc;
		printf("Blad: Wartosc musi byc dodatnia!\n");
	}
}

int pobierzDecyzjeUzytkownika() {
	int decyzja;
	while (1) {
		decyzja = pobierzInt("Twoj wybor: ");
		if (decyzja == 1 || decyzja == 2) return decyzja;
		printf("Blad: Wybierz 1 lub 2.\n");
	}
	return decyzja;
}

int obsluzBladGranic(DaneWejscioweCalkowania* dane) {
	printf("\nCo chcesz zrobic?\n");
	printf("[1] Zamien automatycznie granice miejscami\n[2] Wpisz granice ponownie\n");
	printf("Twoj wybor: ");

	int decyzja = pobierzDecyzjeUzytkownika();

	if (decyzja == 1) {
		zamienLiczby(&dane->poczatekPrzedzialu, &dane->koniecPrzedzialu);
		return 1; 
	}
	return 0; 
}

void wczytajGranice(DaneWejscioweCalkowania* dane) {
	int sukces = 0;
	while (!sukces) {
		dane->poczatekPrzedzialu = pobierzDouble("\nPodaj poczatek przedzialu: ");
		dane->koniecPrzedzialu = pobierzDouble("Podaj koniec przedzialu: ");

		if (dane->poczatekPrzedzialu > dane->koniecPrzedzialu) {
			printf("\nBlad! Poczatek przedzialu (%.2f) jest wiekszy niz koniec (%.2f)\n", dane->poczatekPrzedzialu, dane->koniecPrzedzialu);
			sukces = obsluzBladGranic(dane);
		}
		else {
			sukces = 1;
		}
	}
}

void wczytajWariantObliczen(DaneWejscioweCalkowania* dane) {
	printf("\nWYBRANE GRANICE PRZEDZIAŁU TO: [%.2f, %.2f]\n", dane->poczatekPrzedzialu, dane->koniecPrzedzialu);
	printf("\n~~~~ Dostepne warianty obliczen ~~~~\n");
	printf("1. Liczba podprzedzialow (n)\n2. Zadana dokladnosc\n");
	printf("Wybierz opcje: ");

	if (pobierzDecyzjeUzytkownika() == 1) {
		dane->liczbaPodprzedzialow = pobierzDodatniInt("Podaj liczbe podprzedzialow: ");
	}
	else {
		double dokladnosc = pobierzDodatniDouble("Podaj wymagana dokladnosc: ");
		dane->liczbaPodprzedzialow = (int)(1.0 / dokladnosc);
		if (dane->liczbaPodprzedzialow == 0) dane->liczbaPodprzedzialow = 1;
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
	else {
		perror("Nie udalo sie otworzyc pliku do zapisu");
		return;
	}
}