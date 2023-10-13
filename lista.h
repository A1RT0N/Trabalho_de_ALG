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

    ITEM *lista_remover(LISTA *lista, char *palavra);  

    ITEM lista_busca(LISTA *lista, ITEM item, int level);

    void lista_imprimir(LISTA *lista, char c);

    int lista_apagar(LISTA **lista);
    
    // int lista_tamanho(LISTA *lista);
    int lista_vazia(LISTA *lista);
    int lista_cheia(LISTA *lista);
    
#endif


/*
• insercao str1 str2 : insere a palavra str1, com a definição str2, no dicionário;
• alteracao str1 str2 : altera a definição da palavra str1 para str2;
• remocao str1 : remove a palavra str1 do dicionário;
• busca str1 : imprime a definição da palavra str1;
• impressao ch1 : imprime todas as palavras iniciadas pelo caractere ch1 seguidas por suas respectivas
definições em ordem alfabética. Cada palavra (com sua respectiva definição) deve ser impresso em uma
linha diferente.
*/