#include "lista.h"
#define TAM 5
typedef struct no_ NO;
struct no_{
    ITEM *item;
    NO *proximo;
    NO *abaixo;
    int level;
};

struct skiplist_{
    NO *cabeca; // Sentinela
    int max_level; 

};

NO* recursao_inserir(LISTA* lista, ITEM* item, NO *novo);
int randomico(void);


int randomico(void){
    return rand()%2;
}


LISTA *lista_criar(void){
    LISTA *lista = (LISTA *) malloc(sizeof(LISTA));

    if(lista==NULL) return NULL;

    lista->max_level = TAM; // Escolhemos 5 porque 1/2^5 = 1/32, ou seja, há uma chance de 3% de um nó estar no nível 5

    NO* header = (NO *) malloc(sizeof(NO));
    if(header == NULL) return NULL;

    header->proximo = NULL;
    header->level = 4;

    lista->cabeca = header;

    NO* auxiliar = header;

    if(lista->cabeca == NULL) return NULL;

    for(int i = 0; i < TAM-1; i++){
        NO* novo_header = (NO *) malloc(sizeof(NO));

        novo_header->proximo = NULL;
        novo_header->level = i;

        auxiliar->abaixo = novo_header;
        auxiliar = novo_header;
    }
    
    return (lista);

}

int lista_inserir(LISTA *lista, ITEM *item){
    NO *novo;
    novo = lista->cabeca;

    if(recursao_inserir(lista, item, novo) != NULL) return 1;

    return 0;
}

NO* recursao_inserir(LISTA* lista, ITEM* item, NO *atual){
    NO *analisado_ultimo = NULL;
    while (atual->proximo != NULL && (strcmp(item_get_palavra(atual->proximo->item), item_get_palavra(item)) < 0)) { // Andar horizontalmente
        atual = atual->proximo; // Andar na linha enquanto o próximo for menor que o parâmetro
    }

    if(atual->abaixo != NULL){ // Andar verticalmente
        analisado_ultimo = recursao_inserir(lista,item,atual->abaixo);
    }
    

    if(atual->level == 0 || analisado_ultimo != NULL){ // Vai ter mais coisa
        // inserir o nó
        NO *novo = (NO *) malloc(sizeof(NO));
        if(novo == NULL) return NULL;
        novo->item = item; // O item do novo nó é o item que foi passado como parâmetro no início da função
        novo->proximo = atual->proximo; // Inserir o novo nó na lista parte 1
        novo->abaixo = analisado_ultimo; // O de baixo é o último que foi inserido (se estiver no level 0, o de baixo é NULL)
        novo->level = atual->level; // O level é o mesmo do atual
        atual->proximo = novo; // Inserir o novo nó na lista parte 2
        
        if(randomico() == 1) return novo; 
        return NULL;
    }


}


int lista_alterar(LISTA *lista, ITEM* item);

ITEM *lista_remover(LISTA *lista, ITEM* item); 

ITEM *lista_busca(LISTA *lista, ITEM* item, int level){
    NO *analisado = lista->cabeca->proximo;
    while (strcmp(item_get_palavra(analisado->item), item_get_palavra(item)) < 0) {
        if (analisado->proximo == NULL) {
            if (level == 0) {
                return NULL;
            }
            return lista_busca(lista, analisado->item, level-1);
        }
        analisado = analisado->proximo;
    }
    if (strcmp(item_get_palavra(analisado->item), item_get_palavra(item)) == 0) {
        return analisado->item;
    }
    lista_busca(lista, analisado->item, level-1);
}

void lista_imprimir(LISTA *lista, ITEM* item);

int lista_apagar(LISTA **lista){

}

// int lista_tamanho(LISTA *lista){
//     return lista->tamanho;
// }

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
    