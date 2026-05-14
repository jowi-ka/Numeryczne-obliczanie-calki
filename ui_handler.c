#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "integration.h"

#define MIN_ZAKRES -1000000.0
#define MAX_ZAKRES 1000000.0
#define MIN_EPSILON 0.0000001
#define MAX_EPSILON 1.0
#define MAX_PODPRZEDZIALOW 10000000

static void wyczyscBufor(void) {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

static void zamienLiczby(double* a, double* b) {
	double temp = *a;
	*a = *b;
	*b = temp;
}

static double wczytajLiczbe(const char* komunikat, double min, double max) {
	double wartosc;
	while (1) {
		printf("%s: ", komunikat);
		if (scanf("%lf", &wartosc) == 1) {
			wyczyscBufor();
			if (wartosc >= min && wartosc <= max) return wartosc;
			printf("Blad: Poza zakresem [%.2f, %.2f]\n", min, max);
		}
		else {
			printf("Blad: To nie jest liczba!\n");
			wyczyscBufor();
		}
	}
}

static int obsluzBladGranic(DaneWejscioweCalkowania* dane) {
	printf("\nBlad! Poczatek przedzialu (%.2f) jest wiekszy niz koniec (%.2f)\n",
		dane->poczatekPrzedzialu, dane->koniecPrzedzialu);
	printf("Co chcesz zrobic?\n");
	printf("[1] Zamien automatycznie granice miejscami\n[2] Wpisz granice ponownie\n");

	if ((int)wczytajLiczbe("Twoj wybor", 1, 2) == 1) {
		zamienLiczby(&dane->poczatekPrzedzialu, &dane->koniecPrzedzialu);
		return 1;
	}
	return 0;
}

static void wczytajGranice(DaneWejscioweCalkowania* dane) {
	while (1) {
		dane->poczatekPrzedzialu = wczytajLiczbe("Podaj poczatek przedzialu", MIN_ZAKRES, MAX_ZAKRES);
		dane->koniecPrzedzialu = wczytajLiczbe("Podaj koniec przedzialu", MIN_ZAKRES, MAX_ZAKRES);

		if (dane->poczatekPrzedzialu <= dane->koniecPrzedzialu || obsluzBladGranic(dane))
			break;
	}
}

static void wczytajWariantObliczen(DaneWejscioweCalkowania* dane) {
	printf("\nWYBRANE GRANICE PRZEDZIAŁU TO: [%.2f, %.2f]\n", dane->poczatekPrzedzialu, dane->koniecPrzedzialu);
	printf("\n~~~~ Dostepne warianty obliczen ~~~~\n");
	printf("[1] Liczba podprzedzialow (n)\n[2] Zadana dokladnosc (epsilon)\n");

	int wybor = (int)wczytajLiczbe("Twoj wybor", 1, 2);

	if (wybor == 1) {
		dane->wariant = METODA_PRZEDZIALY;
		dane->liczbaPodprzedzialow = (int)wczytajLiczbe("Podaj n", 1, MAX_PODPRZEDZIALOW);
		dane->epsilon = 0;
	}
	else {
		dane->wariant = METODA_DOKLADNOSC;
		dane->epsilon = wczytajLiczbe("Podaj dokladnosc", MIN_EPSILON, MAX_EPSILON);
		dane->liczbaPodprzedzialow = 0;
	}
}

DaneWejscioweCalkowania wczytajDane() {
	DaneWejscioweCalkowania dane;
	printf("========================================\n");
	printf("   KONFIGURACJA PARAMETRÓW OBLICZEŃ     \n");
	printf("========================================\n");
	wczytajGranice(&dane);
	wczytajWariantObliczen(&dane);
	return dane;
}

void generujRaport(FILE* strumien, const DaneWejscioweCalkowania* dane, double* wyniki, const char** nazwyMetod, int liczbaMetod) {
	fprintf(strumien, "\n--- RAPORT OBLICZEN NUMERYCZNYCH ---\n");
	fprintf(strumien, "Przedzial: [%.2f, %.2f]\n", dane->poczatekPrzedzialu, dane->koniecPrzedzialu);

	if (dane->wariant == METODA_PRZEDZIALY) {
		fprintf(strumien, "Parametr: Liczba podprzedzialow n = %d\n\n", dane->liczbaPodprzedzialow);
	}
	else {
		fprintf(strumien, "Parametr: Dokladnosc epsilon = %f\n\n", dane->epsilon);
	}

	fprintf(strumien, "+---------------------------+--------------------+\n");
	fprintf(strumien, "| %-25s | %-18s |\n", "Metoda calkowania", "Wynik");
	fprintf(strumien, "+---------------------------+--------------------+\n");

	for (int i = 0; i < liczbaMetod; i++) {
		fprintf(strumien, "| %-25s | %18.10f |\n", nazwyMetod[i], wyniki[i]);
	}
	fprintf(strumien, "+---------------------------+--------------------+\n\n");
}

void zapiszWynikiDoPliku(const DaneWejscioweCalkowania* dane, double* wyniki, const char** nazwyMetod, int liczbaMetod) {
	FILE* plik = fopen("wyniki.txt", "w");
	if (!plik) {
		perror("Nie udalo sie otworzyc pliku do zapisu");
		return;
	}
	generujRaport(plik, dane, wyniki, nazwyMetod, liczbaMetod);
	fclose(plik);
	printf("\nWyniki zostaly zapisane do pliku wyniki.txt\n");
}