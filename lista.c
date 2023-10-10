#include "lista.h"

// Lista encadeada ordenada com nó cabeca e circular

typedef struct no_ NO;
struct no_{
    ITEM *item;
    NO *proximo;
};

struct lista_{
    NO* inicio_cabeca; // Sentinela
    NO *fim;
    int tamanho; 
};


LISTA *lista_criar(void){
    LISTA *lista = (LISTA *) malloc(sizeof(LISTA));

    if(lista==NULL) return NULL;

    lista->inicio_cabeca = (NO *) malloc(sizeof(NO));

    if(lista->inicio_cabeca == NULL) return NULL;

    lista->inicio_cabeca->proximo = NULL;
    lista->fim = NULL;
    lista->tamanho = 0;
    return (lista);

}

bool lista_inserir(LISTA *lista, ITEM *item){

}

bool lista_alterar(LISTA *lista, char palavra[], char significado[]);

ITEM *lista_remover(LISTA *lista, char palavra[]); 

ITEM *lista_busca(LISTA *lista, char palavra[]){

    item_set_palavra(&(lista->inicio_cabeca->item), palavra);

    NO *p = lista->inicio_cabeca;   
    do {
    p = p->proximo;
    } while (item_get_chave(p->item) != palavra);

    return ((p != lista->inicio_cabeca) ? p->item : NULL);

}

void lista_imprimir(LISTA *lista, char letra);

bool lista_apagar(LISTA **lista){
    if(!lista_vazia(*lista)){
        for(NO* tmp = (*lista)->inicio_cabeca, *prox; tmp != NULL; ){
            prox = tmp->proximo;
            lista_remover(*lista, item_get_chave(tmp->item));
            tmp = prox;
        }
    }
    free(*lista);
    *lista = NULL;
    return true;
}

int lista_tamanho(LISTA *lista){
    return lista->tamanho;
}

bool lista_vazia(LISTA *lista) {
    if (lista != NULL && (lista->inicio_cabeca->proximo == NULL))   return (true);
    
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
    



// LISTA *lista_criar(void){
//     LISTA *lista = (LISTA *) malloc(sizeof(LISTA));

//     if(lista==NULL) return NULL;

//     lista->inicio = NULL;
//     lista->fim = NULL;
//     lista->tamanho = 0;
//     return (lista);
// }


// // No pior caso você vai percorrer quase no final
// bool lista_inserir_ordenada(LISTA *lista, ITEM *item){  // Se tiver no meio que você quer inserir, não tem jeito, tem que percorrer
//     if(!lista_cheia(lista)){
//         NO* pnovo = (NO *)malloc(sizeof(NO));
//         pnovo->item = item;
//         pnovo->proximo = NULL;
//         lista->tamanho++;
//         if (lista_vazia(lista)){
//             lista->inicio = pnovo;
//             lista->fim = pnovo;
//             return true;
//         }
//         if(item_get_chave(lista->fim->item) <= item_get_chave(pnovo->item)){
//             lista->fim->proximo = pnovo;
//             lista->fim = pnovo;
//             return true;
//         }else{
//             for(NO* i = lista->inicio; i != lista->fim; i = i->proximo){ // Inserir no meio ou no início
//                 if(item_get_chave(i->proximo->item) >= item_get_chave(item)){  // Não preciso checar a outra condição      
//                     pnovo->proximo = i->proximo;
//                     i->proximo = pnovo;
//                     return true;
//                 }
//             }
//         }

//     }
// }


// bool lista_inserir(LISTA *lista, ITEM *item){       
//     if(ORDENADA == 1){
//         lista_inserir_ordenada(lista,item);
//     }else{
//         lista_inserir_fim(lista,item);
//     }
// }


// ITEM* lista_busca(LISTA *lista, char palavra[]){
//     // if(lista != NULL && !lista_vazia(lista)){
//     //     for(NO* i = lista->inicio; i != NULL; i= i->proximo){
//     //         if(item_get_chave(i->item) == chave){
//     //             return i->item;
//     //         }
//     //     }
//     // }
// }

// int lista_tamanho(LISTA *lista){
//     return lista->tamanho;
// }

// bool lista_vazia(LISTA *lista){
//     return(lista->tamanho == 0);
// }

// bool lista_cheia(LISTA *lista){
//     if(lista != NULL){
//         NO* teste = (NO*) malloc(sizeof(NO));
//         if(teste != NULL){
//             free(teste);
//             return false;
//         }
//     }
//     return true;
// }

// ITEM *lista_remover(LISTA *lista, char palavra[]){
    
//     // if (lista != NULL){
//     //     NO *p = lista->inicio; NO *aux = NULL;
//     //     while(p != NULL && (item_get_chave(p->item)) != chave){
//     //         aux = p; 
//     //         p = p->proximo;
//     //     }
//     //     if(p != NULL) {
//     //         if(p == lista->inicio) {
//     //             lista->inicio = p->proximo;
//     //             p->proximo = NULL;
//     //         }
//     //         else {
//     //             aux->proximo = p->proximo;
//     //             p->proximo = NULL;
//     //         }
//     //         if(p == lista->fim){ 
//     //             lista->fim = aux;
//     //         }
//     //         ITEM *it = p->item;
//     //         lista->tamanho--; free(p);
//     //         return (it);
//     // }
//     // }
//     // return (NULL);
// }



// bool lista_apagar(LISTA **lista){
//     if(!lista_vazia(*lista)){
//         for(NO* tmp = (*lista)->inicio, *prox; tmp != NULL; ){
//             prox = tmp->proximo;
//             lista_remover(*lista, item_get_chave(tmp->item));
//             tmp = prox;
//         }
        
//     }
//     free(*lista);
//     *lista = NULL;
//     return true;
// }


// void lista_imprimir(LISTA *lista){
//     if(!lista_vazia(lista)){
//         for(NO* i = lista->inicio; i!= NULL; i= i->proximo){
//             if(i == lista->fim){
//                 printf("[%d];", item_get_chave(i->item));
//             }else{
//                 printf("[%d]; ", item_get_chave(i->item));
//             }

//         }
//     }
// }







