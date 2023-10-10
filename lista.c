#include "lista.h"

// Lista encadeada ordenada com nó cabeca e circular

typedef struct no_ NO;
struct no_{
    ITEM *item;
    NO *proximo;
    NO *abaixo;
    char letra;
};

struct skiplist_{
    NO *sentinela; // Sentinela
    NO *fim;
    int tamanho; 
};


LISTA *lista_criar(void){
    LISTA *lista = (LISTA *) malloc(sizeof(LISTA));

    if(lista==NULL) return NULL;

    lista->sentinela = (NO *) malloc(sizeof(NO));

    if(lista->sentinela == NULL) return NULL;

    lista->sentinela->proximo = NULL;
    lista->fim = NULL;
    lista->tamanho = 0;
    return (lista);

}

bool lista_inserir(LISTA *lista, ITEM *item){

}

bool lista_alterar(LISTA *lista, char *palavra, char *significado);

ITEM *lista_remover(LISTA *lista, char *palavra); 

ITEM *lista_busca(LISTA *lista, char *palavra){

}

void lista_imprimir(LISTA *lista, char letra);

bool lista_apagar(LISTA **lista){

}

int lista_tamanho(LISTA *lista){
    return lista->tamanho;
}

bool lista_vazia(LISTA *lista) {
    if (lista != NULL && (lista->sentinela->proximo == NULL))   return (true);
    
    return (false);
}

bool lista_cheia(LISTA *lista){
    if(lista != NULL){
        NO* teste = (NO*) malloc(sizeof(NO));
        if(teste != NULL){
            free(teste);
            return false;
        }
    }
    return true;
}
    