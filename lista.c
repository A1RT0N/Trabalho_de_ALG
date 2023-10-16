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
int recursao_remover(LISTA* lista, char* palavra, int level);
NO* lista_busca_caracter(LISTA *lista, char c);


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

int lista_inserir(LISTA *lista, ITEM *item) {     /////// OKKKKKKKKKKKK
    NO *novo;

    novo = recursao_inserir(lista, item, lista->cabeca);

    if (novo == NULL) {
        return 1;
    } 
    return 0;

}

int lista_alterar(LISTA *lista, char *palavra, char *significado) {     // OKKKKKKKKKKKKK
    // cria item que servirá para utilizar a busca, usando a palavra que terá o significado alterado
    ITEM *procurado;
    procurado = item_criar(palavra, significado);
    procurado = lista_busca(lista, procurado);

    // muda o significado da palavra
    if (procurado != NULL) {
        item_set_significado(procurado, significado);
        return 1;
    }
    return 0;
}

void lista_remover(LISTA *lista, char *palavra){
    if(recursao_remover(lista, palavra, MAX_LEVEL-1) == 0){
        printf("OPERACAO INVALIDA\n");
    }else{
        return;
    }
}

int recursao_remover(LISTA* lista, char* palavra, int level){
    if (!lista || !palavra || level < 0) return 0;

    NO *analisado = lista->cabeca;

    // desça até o nível de partida
    for (int i = 0; i < (MAX_LEVEL-1 - level); i++) {
        analisado = analisado->abaixo;
    }

    int removed = 0; // para verificar se removemos um nó neste nível

    while (analisado->proximo) {
        if (strcmp(item_get_palavra(analisado->proximo->item), palavra) == 0) {
            // nó com palavra correspondente encontrado, remover
            NO *tmp = analisado->proximo;
            analisado->proximo = tmp->proximo;

            free(tmp->item);
            free(tmp);

            removed = 1;
            break; // uma vez que encontramos e removemos o nó, saímos do loop
        }
        analisado = analisado->proximo;
    }

    // se um nó foi removido neste nível, tentamos remover nos níveis abaixo também
    if (level > 0) {
        return removed + recursao_remover(lista, palavra, level - 1);
    }

    return removed;
}


ITEM* lista_busca(LISTA *lista, ITEM *item_to_search) {
    if (!lista || !item_to_search || !lista->cabeca) {
        return NULL;
    }

    NO *analisado = lista->cabeca;

    while (analisado) {
        // Checa a palavra do próximo nó
        if (analisado->proximo && strcmp(item_get_palavra(analisado->proximo->item), item_get_palavra(item_to_search)) < 0) {
            // Move para o próximo nó caso a palavra seja menor que a procurada
            analisado = analisado->proximo;
        } else {
            if (analisado->proximo && strcmp(item_get_palavra(analisado->proximo->item), item_get_palavra(item_to_search)) == 0) {
                // Se a palavra do próximo nó é a procurada, retorna o item
                return analisado->proximo->item;
            }
            // Se chegou no nível mais baixo e não encontrou, retorna NULL
            if (analisado->nivel == 0) {
                return NULL;
            }
            // Desce um nível
            analisado = analisado->abaixo;
        }
    }

    return NULL;
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