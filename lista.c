#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"
#include "lista.h"

typedef struct no_ {
    struct no_ *proximo;
    struct no_ *abaixo;
    int nivel;
    ITEM *item;
} NO;

struct skiplist_ {
    NO *cabeca;
    int tamanho_maximo;
};

NO* recursao_inserir(LISTA* lista, ITEM* item, NO *atual);
int randomizacao(void);
void imprimir_lista(LISTA *lista);
void recursao_remover(LISTA* lista, char* palavra, NO *anterior);
NO* lista_busca_caracter(LISTA *lista, char c);
NO *lista_inserir(LISTA *lista, ITEM *item, NO *atual);

NO *cabeca(LISTA *lista) {
    if (lista != NULL) {
        return lista->cabeca;
    }
    return NULL;

}
int randomizacao(void) {
    return (rand() % 2);
}

LISTA *lista_criar(void) {  /// OKKKKKKKKKKKKKKKKK
    LISTA *skiplist = (LISTA *)malloc(sizeof(LISTA));

    skiplist->tamanho_maximo = MAX_LEVEL;

    int nivel = MAX_LEVEL - 1;

    NO *header = (NO *)malloc(sizeof(NO));
    header->proximo = NULL;
    header->nivel = nivel;
    header->item = NULL;

    skiplist->cabeca = header;

    NO *aux = header;

    for (int i = 0; i < MAX_LEVEL - 1; i++) {
        nivel--; // Nivel 3,2,1,0

        NO *new_header = (NO *)malloc(sizeof(NO));
        new_header->proximo = NULL;
        new_header->nivel = nivel;
        new_header->item = NULL;

        aux->abaixo = new_header;

        aux = new_header;
    }

    return skiplist;
}

void imprimir_lista(LISTA *lista) {        //////     OKKKKKKKKKKKK
    NO *atual = lista->cabeca;
        for (int i = 0; i < MAX_LEVEL; i++) {  
        while (atual->proximo != NULL) {
            printf("Nivel: %d\n", atual->proximo->nivel);
            printf("Palavra: %s\n", item_get_palavra(atual->proximo->item));
            printf("Significado: %s\n", item_get_significado(atual->proximo->item));
            printf("\n");
            atual = atual->proximo;
        }
        atual = atual->abaixo;
    }

}

NO* recursao_inserir(LISTA* lista, ITEM* item, NO *atual) {   //////// OKKKKKKKKK
    NO *analisado_ultimo = NULL;

    // Encontrar a posição correta para inserir o novo nó
    while (atual->proximo != NULL && strcmp(item_get_palavra(atual->proximo->item), item_get_palavra(item)) < 0) {
        atual = atual->proximo;
    }

    if (atual->abaixo != NULL) {
        analisado_ultimo = recursao_inserir(lista, item, atual->abaixo);
    }

    if (atual->nivel == 0 || analisado_ultimo != NULL) {
        NO *novo = (NO *)malloc(sizeof(NO));
        novo->item = item;
        novo->proximo = atual->proximo;
        novo->abaixo = analisado_ultimo;
        novo->nivel = atual->nivel;
        atual->proximo = novo;

        if (randomizacao() == 1) return novo;
        return NULL;
    }

    return NULL;
}

void lista_insercao(LISTA *lista, char *palavra, char *significado) {
    ITEM *item;
    item = item_criar(palavra, significado);
    lista_inserir(lista, item, lista->cabeca);
}


NO *lista_inserir(LISTA *lista, ITEM *item, NO *atual) {    
    NO *ultimo = NULL;

    while (1) {
        if (atual->proximo == NULL) break;

        if ((atual->proximo != NULL) && (atual->proximo->item != NULL) && (strcmp(item_get_palavra(item), item_get_palavra(atual->proximo->item)))) break;

        atual = atual->proximo;

    }

    if (atual->abaixo != NULL) {
        ultimo = lista_inserir(lista, item, atual->abaixo);
    }

    if (atual->nivel == 0 || (ultimo != NULL)) {
        NO *new_node = (NO *) malloc(sizeof(NO));
        new_node->item = item;
        new_node->abaixo = ultimo;
        new_node->nivel = atual->nivel;
        new_node->proximo = atual->proximo;
        atual->proximo = new_node;

        if (randomizacao() && (atual->nivel < MAX_LEVEL - 1)) {
            return new_node;
        }
    }

    return NULL;

}

int lista_alterar(LISTA *lista, char *palavra, char *significado) {     // OKKKKKKKKKKKKK
    // cria item que servirá para utilizar a busca, usando a palavra que terá o significado alterado
    ITEM *procurado;
    procurado = item_criar(palavra, significado);
    procurado = lista_busca(lista, procurado, lista->cabeca);

    // muda o significado da palavra
    if (procurado != NULL) {
        item_set_significado(procurado, significado);
        return 1;
    }
    return 0;
}

void lista_remover(LISTA *lista, char *palavra, NO *atual) {
    while (1) {
        if (atual->proximo->item == NULL) break;

        if (atual->proximo->item != NULL && !strcmp(palavra, item_get_palavra(atual->proximo->item)) == 0) {
            recursao_remover(lista, palavra, atual);

            return;
        }

        if (atual->proximo->item != NULL && (strcmp(palavra, item_get_palavra(atual->proximo->item)) < 0)) break;

        atual = atual->proximo;
    }

    if (atual->abaixo != NULL) {
        lista_remover(lista, palavra, atual->abaixo);

        return;
    }

}

void recursao_remover(LISTA* lista, char* palavra, NO *anterior) {
    while (strcmp(palavra, item_get_palavra(anterior->proximo->item))) {
        anterior = anterior->proximo;
    }

    NO *tmp = anterior->proximo;
    ITEM *remover_item = tmp->proximo->item;

    tmp->proximo = NULL;

    free(tmp);

    if (anterior->nivel == 0) {
        item_apagar(&remover_item);

        return;
    }

    recursao_remover(lista, palavra, anterior->abaixo);

}


ITEM *lista_busca(LISTA *lista, ITEM *item_to_search, NO *atual) {
    if ((atual->proximo != NULL) && (atual->proximo->item != NULL) && !(strcmp(item_get_palavra(item_to_search), item_get_palavra(atual->proximo->item)))) {
        return atual->proximo->item;
    }

    while (1) {
        if (atual->proximo == NULL) break;

        if ((atual->proximo != NULL) && (atual->proximo->item != NULL) && !(strcmp(item_get_palavra(item_to_search), item_get_palavra(atual->proximo->item)))) return atual->proximo->item;

        if ((atual->proximo != NULL) && (atual->proximo->item != NULL) && (strcmp(item_get_palavra(item_to_search), item_get_palavra(atual->proximo->item)))) break;

        atual = atual->proximo;

    }

    if (atual->abaixo != NULL) {
        return lista_busca(lista, item_to_search, atual->abaixo);
    } else {
        return NULL;
    }
}


void lista_imprimir(LISTA *lista, char c){ // OKKKKKKKKKKKKKKKKK
    NO* primeiro;

    // caso não seja encontrada nenhuma palavra com a letra desejada, o aviso é impresso
    if((primeiro = lista_busca_caracter(lista, c)) == NULL){
        printf("NAO HA PALAVRAS INICIADAS POR %c\n", c);
        return;
    }
    // caso contrário, são impressas as palavras e seus significados que começam com a letra desejada
    while ((primeiro != NULL) && !(item_get_palavra(primeiro->item)[0] != c)) {
        item_imprimir(primeiro->item);
        primeiro = primeiro->proximo;
    }

}

NO* lista_busca_caracter(LISTA *lista, char c) { // OKKKKKKKKKKKKKKK
    if (!lista || !lista->cabeca) {
        return NULL;
    }

    NO *analisado = lista->cabeca;

    while (analisado) {
        // Check the next node's key
        if (analisado->proximo && item_get_palavra(analisado->proximo->item)[0] < c) {
            // Move to the next node if its key is less than the target key
            analisado = analisado->proximo;
        } else {
            if (analisado->proximo && item_get_palavra(analisado->proximo->item)[0] == c) {
                // If next node's key matches the target key, return it
                return analisado->proximo;
            }
            // If we're already on the bottom level and didn't find the item, return NULL
            if (analisado->nivel == 0) {
                return NULL;
            }
            // Move down one level
            analisado = analisado->abaixo;
        }
    }

    return NULL;
}


int lista_apagar(LISTA **lista){
    // definição de dois nós auxiliares para a liberação de memória
    NO *tmp = (*lista)->cabeca;
    NO *prox;
    // int j auxiliar para saber quantos níveis descer antes de ir para direita
    int j = 1;
    for (int i = MAX_LEVEL; i >=0; i--) {
        // free em todos os items e nós do nível
        prox = tmp->proximo;
        while (tmp != NULL) {
            free(tmp->item);
            free(tmp);
            tmp = prox;
            prox = tmp->proximo;
        }
        // descer níveis de acordo com o j (assim passando por todos)
        tmp = (*lista)->cabeca;
        for (int j; j >=0; j++) {
            tmp = tmp->abaixo;
        } 
        j++;
    }
    // free de todos os nós cabeça (um de cada nível)
    tmp = (*lista)->cabeca;
    for (int i = 0; i < MAX_LEVEL; i++) {
        prox = tmp->abaixo;
        free(tmp);
        tmp = prox;
    }

}


int lista_vazia(LISTA *lista) {
    if(lista->cabeca == NULL) return 1;
    return 0;
}

int lista_cheia(LISTA *lista){
    if(lista != NULL){
        NO* teste = (NO*) malloc(sizeof(NO));
        if(teste != NULL){
            free(teste);
            return 0;
        }
    }
    return 1;
}