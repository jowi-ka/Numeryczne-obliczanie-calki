#include "mem_utils.h"
#include <stdio.h>
#include <stdlib.h> 

void* bezpiecznyMalloc(size_t rozmiar, const char* nazwaZmiennej) {
    void* wskaznik = malloc(rozmiar);

    if (wskaznik == NULL) {
        fprintf(stderr, "KRYTYCZNY BLAD: Brak pamieci RAM dla: [%s]!\n", nazwaZmiennej);
        fprintf(stderr, "Program zostanie awaryjnie zamkniety.\n");
        exit(EXIT_FAILURE);
    }

    return wskaznik;
}