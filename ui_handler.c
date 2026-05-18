#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "integration.h"
#include "ui_handler.h"
#include "menu.h"
#include "io_utils.h"
#include "config.h"

static void pokazPrzedzial(const char* komunikat, const DaneWejscioweCalkowania* dane) {
	printf(komunikat, dane->poczatekPrzedzialu, dane->koniecPrzedzialu);
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