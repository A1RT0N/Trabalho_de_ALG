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
NO* lista_busca_caracter(LISTA *lista, ITEM* item, int level);


int randomizacao(void) {
    return rand() % 2;
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

    if (novo != NULL) {
        return 1;
    } else {
        return 0;
    }

}

int lista_alterar(LISTA *lista, char *palavra, char *significado) {
    // cria item que servirá para utilizar a busca, usando a palavra que terá o verbete alterado
    ITEM *procurado;
    procurado = item_criar(palavra, significado);
    printf("oi");
    procurado = lista_busca(lista, procurado);

    printf("passoi");
    // muda o verbete da palavra
    item_set_significado(procurado, significado);
}

void lista_remover(LISTA *lista, char *palavra){
    if(recursao_remover(lista, palavra, MAX_LEVEL) == 0){
        printf("OPERACAO INVALIDA\n");
    }else{
        return;
    }
}

int recursao_remover(LISTA* lista, char* palavra, int level){

    NO *analisado = lista->cabeca->proximo;
    for(int i = 0; i < MAX_LEVEL - level; i++){
        analisado = analisado->abaixo;
    }
    
    while (analisado->proximo != NULL && strcmp(item_get_palavra(analisado->proximo->item), palavra) < 0){
        analisado = analisado->proximo;
    }

    if(level == 0 && strcmp(item_get_palavra(analisado->proximo->item), palavra) != 0){
        return 0;
    }

    if(strcmp(item_get_palavra(analisado->proximo->item), palavra) == 0){
        NO *removido = analisado->proximo;
        analisado->proximo = analisado->proximo->proximo;
        free(removido);
        recursao_remover(lista,palavra, level-1); // Se achou, desce um nível e tenta de novo
        return 1;
    }

    recursao_remover(lista,palavra, level-1); // Se não achou, desce um nível e tenta de novo


}


ITEM* lista_busca(LISTA *lista, ITEM *item_to_search) {
    if (!lista || !item_to_search || !lista->cabeca) {
        return NULL;
    }

    NO *analisado = lista->cabeca;

    while (analisado) {
        // Check the next node's key
        if (analisado->proximo && strcmp(item_get_palavra(analisado->proximo->item), item_get_palavra(item_to_search)) < 0) {
            // Move to the next node if its key is less than the target key
            analisado = analisado->proximo;
        } else {
            if (analisado->proximo && strcmp(item_get_palavra(analisado->proximo->item), item_get_palavra(item_to_search)) == 0) {
                // If next node's key matches the target key, return it
                return analisado->proximo->item;
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


void lista_imprimir(LISTA *lista, char c){
    NO* primeiro;


    if((primeiro = lista_busca_caracter(lista, primeiro->item, MAX_LEVEL)) == NULL){
        printf("NAO HA PALAVRAS INICIADAS POR ch1\n");
        return;
    }
    while (primeiro != NULL && item_get_palavra(primeiro->item)[0] == c) {
        item_imprimir(primeiro->item);
        primeiro = primeiro->proximo;
    }

}

NO* lista_busca_caracter(LISTA *lista, ITEM* item, int level){
    NO *analisado = lista->cabeca->proximo;
    while (item_get_palavra(analisado->item)[0] < item_get_palavra(item)[0]) {
        if (analisado->proximo == NULL) {
            if (level == 0) {
                return NULL;
            }
            return lista_busca_caracter(lista, analisado->item, level-1);
        }
        analisado = analisado->proximo;
    }
    if ((item_get_palavra(analisado->item)[0] == item_get_palavra(item)[0])) {
        return analisado;
    }
    lista_busca_caracter(lista, analisado->item, level-1);
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
