#pragma once

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

typedef double (*MetodaCalkowania)(const DaneWejscioweCalkowania*);

double obliczMetodaProstokatow(const DaneWejscioweCalkowania* dane);
double obliczMetodaTrapezow(const DaneWejscioweCalkowania* dane);
double obliczMetodaMonteCarlo(const DaneWejscioweCalkowania* dane);
