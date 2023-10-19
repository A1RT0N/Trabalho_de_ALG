#ifndef LISTA_H
    #define LISTA_H

    #define inicial 0
    #define ERRO -32000
    #define ORDENADA 1  
    #define MAX_LEVEL 15
    
    typedef struct skiplist_ LISTA;

    #include "item.h"

    typedef struct no_ NO;

    NO *cabeca(LISTA *lista);

    void lista_insercao(LISTA *lista, ITEM *item);

    LISTA *lista_criar(void);
    
    int lista_alterar(LISTA *lista, char *palavra, char *significado);

    void lista_remover(LISTA *lista, ITEM *item, NO *atual);  

    void recursao_remover(LISTA *lista, ITEM *item, NO *anterior);

    ITEM* lista_busca(LISTA *lista, ITEM* item, NO *atual);

    void imprimir_lista(LISTA *lista);

    void lista_imprimir(LISTA *lista, char c);

    int lista_apagar(LISTA **lista);
    
    int lista_vazia(LISTA *lista);
    int lista_cheia(LISTA *lista);
    
#endif