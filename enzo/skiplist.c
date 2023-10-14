#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "item.h"
#include "skiplist.h"

struct skiplist_{
    NO *header;

    int tamanho_maximo;
};  

struct no {
    NO *proximo; //proximo nó do mesmo nivel
    NO *abaixo; //no do nivel abaixo

    int nivel;

    ITEM *item;
};

int randomizacao(){
    return rand() % 2;
}

SKIPLIST* skiplist_criar(){
    SKIPLIST *skiplist = (SKIPLIST *) malloc(sizeof(SKIPLIST));

    skiplist->tamanho_maximo = TAM_MAX;

    int nivel = TAM_MAX - 1;

    NO *header = (NO *) malloc(sizeof(NO));
    header->proximo = NULL;
    header->nivel = nivel;

    skiplist->header = header;
    
    NO *aux = header;

    for (int i = 0; i < TAM_MAX - 1; i++){
        nivel--;

        NO *new_header = (NO *) malloc(sizeof(NO));
        new_header->proximo = NULL;
        new_header->nivel = nivel;

        aux->abaixo = new_header; 

        aux = new_header;
    }

    return skiplist;
}

ITEM* skiplist_busca(SKIPLIST *skiplist, ITEM *item, NO *atual){
   if ((atual->proximo == NULL) && (atual->abaixo != NULL)) { //fim da lista e níveis disponíveis abaixo
        //descer de nível
        return skiplist_busca(skiplist, item, atual->abaixo); 
    } else if ((atual->proximo != NULL) && item_comparar(item, atual->proximo->item)){ //se próximo item menor, ir para ele
        //avançar na lista
        return skiplist_busca(skiplist, item, atual->proximo);
    } else if(atual->abaixo != NULL) {//se vc ainda não estiver no menor nível
        //descer de nível
        return skiplist_busca(skiplist, item, atual->abaixo);
    }

    if (item_igual(item, atual->item)) return atual->item;

    return NULL;
}

NO* skiplist_inserir(SKIPLIST *skiplist, ITEM *item, NO *atual){
    NO *ultimo = NULL;

    if ((atual->proximo == NULL) && (atual->abaixo != NULL)) { //fim da lista e níveis disponíveis abaixo
        //descer de nível
        ultimo = skiplist_inserir(skiplist, item, atual->abaixo); 
    } else if ((atual->proximo != NULL) && item_comparar(item, atual->proximo->item)){ //se próximo item menor, ir para ele
        //avançar na lista
        ultimo = skiplist_inserir(skiplist, item, atual->proximo);
    } else if(atual->abaixo != NULL) {//se vc ainda não estiver no menor nível
        //descer de nível
        ultimo = skiplist_inserir(skiplist, item, atual->abaixo);
    }

    if(atual->proximo != NULL && item_comparar(item, atual->proximo->item)) atual = atual->proximo;
    
    int randomizar = randomizacao();

    if (((atual->nivel == 0) && (ultimo == NULL)) || (randomizar && ultimo != NULL && atual->nivel != ultimo->nivel)){
        printf("Inserindo no nivel: %d\n", atual->nivel);
        NO *new_node = (NO *) malloc(sizeof(NO));

        new_node->item = item;

        new_node->abaixo = ultimo;
        new_node->nivel = atual->nivel;


        new_node->proximo = atual->proximo;
        atual->proximo = new_node;

        return new_node;
    }

    return NULL;
}

void skiplist_remover(SKIPLIST* skiplist, ITEM* item, NO* atual) {
    if (atual == NULL) {
        // Nó não encontrado, retornar algum valor para indicar falha
        return;
    }

    if (atual->proximo == NULL) {
        if (atual->abaixo != NULL) {
            // Desça para a próxima camada e continue procurando
            return skiplist_remover(skiplist, item, atual->abaixo);
        } else {
            // Nó não encontrado, retornar algum valor para indicar falha
            return;
        }
    }

    if (item_igual(atual->proximo->item, item)) {
        while (1){
            NO* tmp = atual;

            atual = atual->abaixo;

            NO *apagar = tmp->proximo;

            tmp->proximo = apagar->proximo;

            if (tmp->nivel == 0){
                item_apagar(&(apagar->item));

                free(apagar);

                return;
            }

            free(apagar);
        }
        
        return; //nao sei oq retornar quando sucesso
    } else if (item_comparar(item, atual->proximo->item)) {
        return skiplist_remover(skiplist, item, atual->proximo);
    } else {
        if (atual->abaixo != NULL) {
            return skiplist_remover(skiplist, item, atual->abaixo);
        } else {
            return;
        }
    }
}

NO* skiplist_header(SKIPLIST *skiplist){
    return skiplist->header;
}

ITEM * skiplist_no_item(NO* no){
    item_imprimir(no->item);
    //return no->item;
}

void niveis(SKIPLIST *skiplist){
    NO *p = skiplist->header;

    while (p != NULL){
        NO *p2;
        printf("Nivel: %d|", p->nivel);

        if (p->proximo != NULL){
            p2 = p->proximo;
                
                while (p2 != NULL){
                    printf("%s ", item_get_chave(p2->item));

                    p2 = p2->proximo;
                }
        } else{
            printf("Nao tem nada");
        }

        printf("\n");

        p = p->abaixo;
    }
}