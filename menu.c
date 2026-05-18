#include <stdio.h>

void wyswietlMenu(const char* tytul, const char* opcje[], int liczbaOpcji) {
	printf("\n%s\n", tytul);
	for (int i = 0; i < liczbaOpcji; i++) {
		printf("[%d] %s\n", i + 1, opcje[i]);
	}
}