#ifndef LISTA_H
    #define LISTA_H

    #define inicial 0
    #define ERRO -32000
    #define ORDENADA 1  
    #define MAX_LEVEL 5
    
    typedef struct skiplist_ LISTA;

    #include "item.h"

    LISTA *lista_criar(void);

    int lista_inserir(LISTA *lista, ITEM *item);
    
    int lista_alterar(LISTA *lista, char *palavra, char *significado);

    void lista_remover(LISTA *lista, char *palavra);  

    ITEM* lista_busca(LISTA *lista, ITEM* item);

    void imprimir_lista(LISTA *lista);

    void lista_imprimir(LISTA *lista, char c);

    int lista_apagar(LISTA **lista);
    
    int lista_vazia(LISTA *lista);
    int lista_cheia(LISTA *lista);
    
#endif