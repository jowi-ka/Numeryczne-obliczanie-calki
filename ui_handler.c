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

static bool czyGranicePoprawne(double poczatekPrzedzialu, double koniecPrzedzialu) {
	return poczatekPrzedzialu <= koniecPrzedzialu;
}

static bool czyWZakresieDouble(double x, double min, double max) {
	return x >= min && x <= max;
}

static bool czyWZakresieInt(int x, int min, int max) {
	return x >= min && x <= max;
}

static bool czyPobranoDouble(double* wartosc) {
	
	if (scanf("%lf", wartosc) != 1) {
		wyczyscBufor();
		return false;
	}

	wyczyscBufor();
	return true;
}

static bool czyPobranoInt(int* wartosc) {

	if (scanf("%d", wartosc) != 1) {
		wyczyscBufor();
		return false;
	}

	wyczyscBufor();
	return true;
}

static double wczytajLiczbeDouble(const char* komunikat, double min, double max) {
	double wartosc;
	while (1) {
		printf("%s: ", komunikat);
		
		if (!czyPobranoDouble(&wartosc)) {
			printf("Blad: To nie jest liczba!\n");
			continue;
		}

		if (!czyWZakresieDouble(wartosc, min, max)) {
			printf("Blad: Poza zakresem [%.2f, %.2f]\n", min, max);
			continue;
		}

		return wartosc;
	}
}

static int wczytajLiczbeInt(const char* komunikat, int min, int max) {
    int wartosc;
    while (1) {
        printf("%s: ", komunikat);

        if (!czyPobranoInt(&wartosc)) {
            printf("Blad: To nie jest liczba calkowita!\n");
            continue;
        }

		if (!czyWZakresieInt(wartosc, min, max)) {
            printf("Blad: Poza zakresem [%d, %d]\n", min, max);
            continue;
        }

        return wartosc;
    }
}

static void wyswietlMenu(const char* tytul, const char* opcje[], int liczbaOpcji) {
	printf("\n%s\n", tytul);
	for (int i = 0; i < liczbaOpcji; i++) {
		printf("[%d] %s\n", i + 1, opcje[i]);
	}
}


static void obsluzBladGranic(DaneWejscioweCalkowania* dane) {
	printf("\nBlad! Poczatek przedzialu (%.2f) jest wiekszy niz koniec (%.2f)\n",
		dane->poczatekPrzedzialu, dane->koniecPrzedzialu);

	const char* opcje[] = {
		"Zamien automatycznie granice miejscami",
		"Wpisz granice ponownie"
	};

	wyswietlMenu("Co chcesz zrobic?", opcje, 2);

	int wybor = wczytajLiczbeInt("Twoj wybor", 1, 2);

	if (wybor == 1) {
		zamienLiczby(&dane->poczatekPrzedzialu, &dane->koniecPrzedzialu);
		printf("\nZamieniono granice.\n");
	}
}

static void pobierzGranice(double* poczatekPrzedzialu, double* koniecPrzedzialu) {
	*poczatekPrzedzialu = wczytajLiczbeDouble("Podaj poczatek przedzialu", MIN_ZAKRES, MAX_ZAKRES);
	*koniecPrzedzialu = wczytajLiczbeDouble("Podaj koniec przedzialu", MIN_ZAKRES, MAX_ZAKRES);
}


static void wczytajGranice(DaneWejscioweCalkowania* dane) {

	pobierzGranice(&dane->poczatekPrzedzialu, &dane->koniecPrzedzialu);

	while (!czyGranicePoprawne(dane->poczatekPrzedzialu, dane->koniecPrzedzialu)) {

		obsluzBladGranic(dane);

		if (!czyGranicePoprawne(dane->poczatekPrzedzialu, dane->koniecPrzedzialu)) {
			pobierzGranice(&dane->poczatekPrzedzialu, &dane->koniecPrzedzialu);
		}
	}
	printf("Przedzial do obliczen: [%.2f, %.2f]\n",
		dane->poczatekPrzedzialu,
		dane->koniecPrzedzialu);
}

static void wczytajWariantObliczen(DaneWejscioweCalkowania* dane) {
	const char* opcje[] = {
	"Liczba podprzedzialow",
	"Zadana dokladnosc"
	};

	int liczbaOpcji = sizeof(opcje) / sizeof(opcje[0]);
	
	wyswietlMenu(
		"~~~~ Dostepne warianty obliczen ~~~~",
		opcje,
		liczbaOpcji);

	int wybor = wczytajLiczbeInt("Twoj wybor", 1, liczbaOpcji);

	if (wybor == 1) {
		dane->wariant = METODA_PRZEDZIALY;
		dane->liczbaPodprzedzialow = wczytajLiczbeInt("Podaj n", 1, MAX_PODPRZEDZIALOW);
		dane->epsilon = 0;
	}
	else {
		dane->wariant = METODA_DOKLADNOSC;
		dane->epsilon = wczytajLiczbeDouble("Podaj dokladnosc", MIN_EPSILON, MAX_EPSILON);
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