#pragma once
#define LICZBA_METOD 3

typedef enum {
    METODA_PRZEDZIALY,
    METODA_DOKLADNOSC
} WariantObliczen;

typedef struct {
    double poczatekPrzedzialu;
    double koniecPrzedzialu;
    int liczbaPodprzedzialow;
    double epsilon;
    WariantObliczen wariant;
} DaneWejscioweCalkowania;


double obliczMetodaProstokatow(DaneWejscioweCalkowania dane);
double obliczMetodaTrapezow(DaneWejscioweCalkowania dane);
double obliczMetodaMonteCarlo(DaneWejscioweCalkowania dane);

