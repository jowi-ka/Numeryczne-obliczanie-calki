#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "logic.h"
#include "integration.h"


void zamienLiczby(double* a, double* b) {
	double temp = *a;
	*a = *b;
	*b = temp;
}

bool czyGranicePoprawne(DaneWejscioweCalkowania* dane) {
	return dane->poczatekPrzedzialu <= dane->koniecPrzedzialu;
}

bool czyWZakresieDouble(double x, double min, double max) {
	return x >= min && x <= max;
}

bool czyWZakresieInt(int x, int min, int max) {
	return x >= min && x <= max;
}
