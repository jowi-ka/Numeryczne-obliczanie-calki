#define _CRT_SECURE_NO_WARNINGS
#include "reports.h"

void generujRaport(FILE* strumien, const DaneWejscioweCalkowania* dane, const double* wyniki, const char** nazwyMetod, int liczbaMetod) {
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

void zapiszWynikiDoPliku(const DaneWejscioweCalkowania* dane, const double* wyniki, const char** nazwyMetod, int liczbaMetod) {
	FILE* plik = fopen("wyniki.txt", "w");
	if (!plik) {
		perror("Nie udalo sie otworzyc pliku do zapisu");
		return;
	}
	generujRaport(plik, dane, wyniki, nazwyMetod, liczbaMetod);
	fclose(plik);
	printf("\nWyniki zostaly zapisane do pliku wyniki.txt\n");
}