#ifndef REPORTS_H
#define REPORTS_H

#include <stdio.h>
#include "integration.h"

void generujRaport(FILE* strumien, const DaneWejscioweCalkowania* dane, const double* wyniki, const char** nazwyMetod, int liczbaMetod);
void zapiszWynikiDoPliku(const DaneWejscioweCalkowania* dane, const double* wyniki, const char** nazwyMetod,int liczbaMetod);

#endif