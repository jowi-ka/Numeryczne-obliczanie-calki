#include "integration.h"
#include <math.h>
#include <stdlib.h>

// Zdefiniowanie funkcji(np. f(x) = x^2)
double f(double x) {
    return x * x;
}

// --- POMOCNICZE ALGORYTMY MATEMATYCZNE ---

double algorytmProstokatow(double a, double b, int n) {
    double h = (b - a) / n;
    double suma = 0.0;
    for (int i = 0; i < n; i++) {
        suma += f(a + (i + 0.5) * h);
    }
    return suma * h;
}

double algorytmTrapezow(double a, double b, int n) {
    double h = (b - a) / n;
    double suma = (f(a) + f(b)) / 2.0;
    for (int i = 1; i < n; i++) {
        suma += f(a + i * h);
    }
    return suma * h;
}

double algorytmMonteCarlo(double a, double b, int n) {
    double max_y = 10.0; // Ustal to na podstawie swojej funkcji!
    int trafienia = 0;
    for (int i = 0; i < n; i++) {
        double x = a + ((double)rand() / RAND_MAX) * (b - a);
        double y = ((double)rand() / RAND_MAX) * max_y;
        if (y <= f(x)) trafienia++;
    }
    return (double)trafienia / n * (b - a) * max_y;
}

// --- GŁÓWNE FUNKCJE ---
double obliczMetodaProstokatow(DaneWejscioweCalkowania dane) {
    if (dane.wariant == METODA_PRZEDZIALY) {
        return
            algorytmProstokatow(dane.poczatekPrzedzialu, dane.koniecPrzedzialu, dane.liczbaPodprzedzialow);
    }
    else {
        int n = 1;
        double poprz, akt = algorytmProstokatow(dane.poczatekPrzedzialu, dane.koniecPrzedzialu, n);
        do {
            poprz = akt;
            n *= 2;
            akt = algorytmProstokatow(dane.poczatekPrzedzialu, dane.koniecPrzedzialu, n);
        } while (fabs(akt - poprz) > dane.epsilon);
        return akt;
    }
}

double obliczMetodaTrapezow(DaneWejscioweCalkowania dane) {
    if (dane.wariant == METODA_PRZEDZIALY) {
        return algorytmTrapezow(dane.poczatekPrzedzialu, dane.koniecPrzedzialu, dane.liczbaPodprzedzialow);
    }
    else {
        int n = 1;
        double poprz, akt = algorytmTrapezow(dane.poczatekPrzedzialu, dane.koniecPrzedzialu, n);
        do {
            poprz = akt;
            n *= 2;
            akt = algorytmTrapezow(dane.poczatekPrzedzialu, dane.koniecPrzedzialu, n);
        } while (fabs(akt - poprz) > dane.epsilon);
        return akt;
    }
}

double obliczMetodaMonteCarlo(DaneWejscioweCalkowania dane) {
    if (dane.wariant == METODA_PRZEDZIALY) {
        return algorytmMonteCarlo(dane.poczatekPrzedzialu, dane.koniecPrzedzialu, dane.liczbaPodprzedzialow);
    }
    else {
        int n = 100;
        double poprz, akt = algorytmMonteCarlo(dane.poczatekPrzedzialu, dane.koniecPrzedzialu, n);
        do {
            poprz = akt;
            n *= 2;
            akt = algorytmMonteCarlo(dane.poczatekPrzedzialu, dane.koniecPrzedzialu, n);
        } while (fabs(akt - poprz) > dane.epsilon);
        return akt;
    }
}
