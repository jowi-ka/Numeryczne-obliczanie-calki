#ifndef INTEGRATION_H
#define INTEGRATION_H

double obliczMetodaProstokatow(double poczatekPrzedzialu, double koniecPrzedzialu, int liczbaPodprzedzialow);
double obliczMetodaTrapezow(double poczatekPrzedzialu, double koniecPrzedzialu, int liczbaPodprzedzialow);
double obliczMetodaMonteCarlo(double poczatekPrzedzialu, double koniecPrzedzialu, int liczbaPodprzedzialow);


#endif