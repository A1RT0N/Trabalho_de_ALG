#ifndef ITEM_H
	#define ITEM_H

	#include <stdbool.h>
    #include <stdlib.h>
    #include <stdio.h>
	#include <string.h>
	#include <time.h>

	typedef struct item_ ITEM;

	ITEM* item_criar(char palavra[], char significado[]);
	int item_apagar(ITEM **item);
	void item_imprimir(ITEM *item);
	char* item_get_palavra(ITEM *item);
	int item_set_palavra(ITEM *item, char palavra[]);
	int item_set_significado(ITEM *item, char significado[]);

	int item_maior(ITEM* item_novo, ITEM* item);


#endif
