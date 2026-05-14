#ifndef INTEGRATION_H
#define INTEGRATION_H
#include <stdio.h> 

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


// Funkcje UI
DaneWejscioweCalkowania wczytajDane();
void generujRaport(FILE* strumien, const DaneWejscioweCalkowania* dane, double* wyniki, const char** nazwyMetod, int liczbaMetod);
void zapiszWynikiDoPliku(const DaneWejscioweCalkowania* dane, double* wyniki, const char** nazwyMetod, int liczbaMetod);
// Funkcje obliczeniowe 
double obliczMetodaProstokatow(DaneWejscioweCalkowania dane);
double obliczMetodaTrapezow(DaneWejscioweCalkowania dane);
double obliczMetodaMonteCarlo(DaneWejscioweCalkowania dane);

#endif