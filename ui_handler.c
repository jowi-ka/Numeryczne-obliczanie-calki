#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "integration.h"
#include "ui_handler.h"
#include "menu.h"

#define MIN_ZAKRES -1000000.0
#define MAX_ZAKRES 1000000.0
#define MIN_EPSILON 0.0000001
#define MAX_EPSILON 1.0
#define MAX_PODPRZEDZIALOW 10000000


static void pokazPrzedzial(const char* komunikat, const DaneWejscioweCalkowania* dane) {
	printf(komunikat, dane->poczatekPrzedzialu, dane->koniecPrzedzialu);
}

static void wyczyscBufor(void) {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
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

static void pobierzGranice(DaneWejscioweCalkowania* dane) {
	dane->poczatekPrzedzialu = wczytajLiczbeDouble("Podaj poczatek przedzialu", MIN_ZAKRES, MAX_ZAKRES);
	dane->koniecPrzedzialu = wczytajLiczbeDouble("Podaj koniec przedzialu", MIN_ZAKRES, MAX_ZAKRES);
}

static void akcjaZamienGranice(DaneWejscioweCalkowania* dane) {
	zamienLiczby(&dane->poczatekPrzedzialu, &dane->koniecPrzedzialu);
	printf("\nZamieniono granice.\n");
}

static void akcjaWprowadzPonownie(DaneWejscioweCalkowania* dane) {
	pobierzGranice(dane);
}

static void akcjaWybierzMetodePrzedzialy(DaneWejscioweCalkowania* dane) {
	dane->wariant = METODA_PRZEDZIALY;
	dane->liczbaPodprzedzialow = wczytajLiczbeInt("Podaj n", 1, MAX_PODPRZEDZIALOW);
	dane->epsilon = 0;
}

static void akcjaWybierzMetodeDokladnosc(DaneWejscioweCalkowania* dane) {
	dane->wariant = METODA_DOKLADNOSC;
	dane->epsilon = wczytajLiczbeDouble("Podaj dokladnosc", MIN_EPSILON, MAX_EPSILON);
	dane->liczbaPodprzedzialow = 0;
}

typedef void (*AkcjaWyboru)(DaneWejscioweCalkowania*);

static AkcjaWyboru akcjeObslugiBleduGranic[] = {
	akcjaZamienGranice,
	akcjaWprowadzPonownie
};

static AkcjaWyboru akcjeWczytaniaWariantuObliczen[] = {
	akcjaWybierzMetodePrzedzialy,
	akcjaWybierzMetodeDokladnosc
};

static void obsluzBladGranic(DaneWejscioweCalkowania* dane) {
	const char* opcje[] = {
		"Zamien automatycznie granice miejscami",
		"Wpisz granice ponownie"
	};
	const int liczbaOpcji = sizeof(opcje) / sizeof(opcje[0]);
	pokazPrzedzial("\nBlad! Poczatek przedzialu (%.2f) jest wiekszy niz koniec (%.2f)\n", dane);
	wyswietlMenu("Co chcesz zrobic?", opcje, liczbaOpcji);
	int wybor = wczytajLiczbeInt("Twoj wybor", 1, liczbaOpcji);
	akcjeObslugiBleduGranic[wybor - 1](dane);
}

static void wczytajGranice(DaneWejscioweCalkowania* dane) {
	pobierzGranice(dane);
	while (!czyGranicePoprawne(dane)) obsluzBladGranic(dane);
	pokazPrzedzial("Przedzial do obliczen: [%.2f, %.2f]\n", dane);
}

static void wczytajWariantObliczen(DaneWejscioweCalkowania* dane) {
	const char* opcje[] = {
	"Liczba podprzedzialow",
	"Zadana dokladnosc"
	};
	int liczbaOpcji = sizeof(opcje) / sizeof(opcje[0]);
	wyswietlMenu("~~~~ Dostepne warianty obliczen ~~~~", opcje, liczbaOpcji);
	int wybor = wczytajLiczbeInt("Twoj wybor", 1, liczbaOpcji);
	akcjeWczytaniaWariantuObliczen[wybor - 1](dane);
}

void wczytajDane(DaneWejscioweCalkowania* dane) {
	if (dane == NULL) return;

	printf("========================================\n");
	printf("   KONFIGURACJA PARAMETROW OBLICZEN    \n");
	printf("========================================\n\n");

	wczytajGranice(dane);
	wczytajWariantObliczen(dane);
}