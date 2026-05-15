#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "integration.h"
#include "ui_handler.h"

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
	printf("\nBlad! Poczatek przedzialu (%.2f) jest wiekszy niz koniec (%.2f)\n", dane->poczatekPrzedzialu, dane->koniecPrzedzialu);
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
	printf("[1] Liczba podprzedzialow \n[2] Zadana dokladnosc\n");

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

void wczytajDane(DaneWejscioweCalkowania* dane) {
	if (dane == NULL) return;

	printf("========================================\n");
	printf("   KONFIGURACJA PARAMETROW OBLICZEN    \n");
	printf("========================================\n\n");

	wczytajGranice(dane);
	wczytajWariantObliczen(dane);
}
