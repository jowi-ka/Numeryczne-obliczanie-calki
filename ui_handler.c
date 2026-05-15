#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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

static bool czyWZakresie(double x, double min, double max) {
	return x >= min && x <= max;
}

static int wczytajDouble(double* wartosc) {
	if (scanf("%lf", wartosc) == 1) {
		wyczyscBufor();
		return 1;
	}

	wyczyscBufor();
	return 0;
}

static double wczytajLiczbe(const char* komunikat, double min, double max) {
	double wartosc;
	while (1) {
		printf("%s: ", komunikat);
		
		if (!wczytajDouble(&wartosc)) {
			printf("Blad: To nie jest liczba!\n");
			continue;
		}

		if (!czyWZakresie(wartosc, min, max)) {
			printf("Blad: Poza zakresem [%.2f, %.2f]\n", min, max);
			continue;
		}

		return wartosc;
	}
}

static int pokazMenu(
	const char* tytul,
	const char* opcje[],
	int liczbaOpcji)
{
	printf("\n%s\n", tytul);

	for (int i = 0; i < liczbaOpcji; i++) {
		printf("[%d] %s\n", i + 1, opcje[i]);
	}

	return (int)wczytajLiczbe(
		"Twoj wybor",
		1,
		liczbaOpcji
	);
}

static int obsluzBladGranic(DaneWejscioweCalkowania* dane) {
	printf("\nBlad! Poczatek przedzialu (%.2f) jest wiekszy niz koniec (%.2f)\n", dane->poczatekPrzedzialu, dane->koniecPrzedzialu);

	const char* opcje[] = {
		"Zamien automatycznie granice miejscami",
		"Wpisz granice ponownie"
	};

	int wybor = pokazMenu(
		"Co chcesz zrobic?",
		opcje,
		sizeof(opcje) / sizeof(opcje[0])
	);

	if (wybor == 1) {
		zamienLiczby(&dane->poczatekPrzedzialu, &dane->koniecPrzedzialu);

		printf("\nZamieniono granice.\n");
	}


	return (wybor == 1);
}

static void wczytajGranice(DaneWejscioweCalkowania* dane) {
	while (1) {
		dane->poczatekPrzedzialu = wczytajLiczbe("Podaj poczatek przedzialu", MIN_ZAKRES, MAX_ZAKRES);
		dane->koniecPrzedzialu = wczytajLiczbe("Podaj koniec przedzialu", MIN_ZAKRES, MAX_ZAKRES);

		if (dane->poczatekPrzedzialu <= dane->koniecPrzedzialu || obsluzBladGranic(dane))
			break;
	}

	printf("Aktualny przedzial: [%.2f, %.2f]\n",
		dane->poczatekPrzedzialu,
		dane->koniecPrzedzialu);
}

static void wczytajWariantObliczen(DaneWejscioweCalkowania* dane) {
	const char* opcje[] = {
	"Liczba podprzedzialow",
	"Zadana dokladnosc"
	};

	int wybor = pokazMenu(
		"~~~~ Dostepne warianty obliczen ~~~~",
		opcje,
		sizeof(opcje) / sizeof(opcje[0])
	);

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