#ifndef ITEM_H
	#define ITEM_H

	#include <stdbool.h>
    #include <stdlib.h>
    #include <stdio.h>
	#include <string.h>
	#include <stdbool.h>

	typedef struct item_ ITEM;

	ITEM* item_criar(char palavra[], char significado[]);
	bool item_apagar(ITEM **item);
	void item_imprimir(ITEM *item);
	char* item_get_palavra(ITEM *item);
	bool item_set_palavra(ITEM *item, char palavra[]);
	bool item_set_significado(ITEM *item, char significado[]);

	bool item_maior(ITEM* item_novo, ITEM* item);


#endif
