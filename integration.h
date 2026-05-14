#ifndef INTEGRATION_H
#define INTEGRATION_H

// Struktura danych dla danych wejściowych
typedef struct {
	double poczatekPrzedzialu;
	double koniecPrzedzialu;
	int liczbaPodprzedzialow;
}DaneWejscioweCalkowania;

// Funkcje UI
DaneWejscioweCalkowania pobierzDane();
void wyswietlRaport(DaneWejscioweCalkowania dane, double wynikMetodyProstokatow, double wynikMetodyTrapezow, double wynikMetodyMonteCarlo);
void zapiszWynikiDoPliku(DaneWejscioweCalkowania dane, double wynikMetodyProstokatow, double wynikMetodyTrapezow, double wynikMetodyMonteCarlo);

// Funkcje obliczeniowe 
double obliczMetodaProstokatow(DaneWejscioweCalkowania dane);
double obliczMetodaTrapezow(DaneWejscioweCalkowania dane);
double obliczMetodaMonteCarlo(DaneWejscioweCalkowania dane);


#endif