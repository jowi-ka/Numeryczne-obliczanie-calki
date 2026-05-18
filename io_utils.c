#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include "logic.h"

void wyczyscBufor(void) {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

bool czyPobranoDouble(double* wartosc) {
	if (scanf("%lf", wartosc) != 1) {
		wyczyscBufor();
		return false;
	}
	wyczyscBufor();
	return true;
}

bool czyPobranoInt(int* wartosc) {
	if (scanf("%d", wartosc) != 1) {
		wyczyscBufor();
		return false;
	}
	wyczyscBufor();
	return true;
}

double wczytajLiczbeDouble(const char* komunikat, double min, double max) {
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

int wczytajLiczbeInt(const char* komunikat, int min, int max) {
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
