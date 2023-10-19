#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"
#include "lista.h"

// definição da struct nó, que será chamado NO
typedef struct no_ {
    struct no_ *proximo;
    struct no_ *abaixo;
    int nivel;
    ITEM *item;
} NO;

// definição da struct skiplist, que será chamada apenas LISTA
struct skiplist_ {
    NO *cabeca;
    int tamanho_maximo;
};

// algumas declarações que serão utilizadas ao longo do código
int randomizacao(void);
void imprimir_lista(LISTA *lista);
void recursao_remover(LISTA* lista, ITEM *item, NO *anterior);
NO* lista_busca_caracter(LISTA *lista, char c);
NO *lista_inserir(LISTA *lista, ITEM *item, NO *atual);

// função que retorna o nó cabeça da lista
NO *cabeca(LISTA *lista) {
    if (lista != NULL) {
        return lista->cabeca;
    }
    return NULL;

}

// função que retorna 0 ou 1, com uma chance de 50% de cada (será utilizado para a criação de níveis maiores
// da skiplist)
int randomizacao(void) {
    return (rand() % 2);
}


// função que cria a skiplist, alocando os espaços, a cabeça, definindo seu tamanho máximo de níveis e retornando
// seu ponteiro
LISTA *lista_criar(void) {  
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

// função que imprime a lista completa (essa função foi utilizada com o intuito de achar possíveis erros na 
// lógica enquanto fazíamos a depuração do código)
void imprimir_lista(LISTA *lista) {
    NO *atual = lista->cabeca;
    int descer = 0;
        for (int i = 0; i < MAX_LEVEL; i++) {  
        atual = lista->cabeca;
        for (int i = 0; i < descer; i++) {
            atual = atual->abaixo;
        }
        while (atual->proximo != NULL) {
            printf("Nivel: %d\n", atual->proximo->nivel);
            printf("Palavra: %s\n", item_get_palavra(atual->proximo->item));
            printf("Significado: %s\n", item_get_significado(atual->proximo->item));
            printf("\n");
            atual = atual->proximo;
            
        }
        descer++;
        
    }

}



// lista inserção apenas chama a lista inserir com o nó cabeça como argumento
void lista_insercao(LISTA *lista, ITEM *item) {

    if(lista_busca(lista, item, lista->cabeca) != NULL) {
        printf("OPERACAO INVALIDA\n"); 
        return;
    };

    lista_inserir(lista, item, lista->cabeca);
}


NO *lista_inserir(LISTA *lista, ITEM *item, NO *atual) {     
    NO *ultimo = NULL;
    // definição de um nó que representará o último nó analisado

    // laço que só quebrará quando o próximo for NULL
    while (1) {
        if (atual->proximo == NULL) break;
        // move para o próximo enquanto ele for menor, não nulo e o item do próximo também não for nulo
        if ((atual->proximo != NULL) && (atual->proximo->item != NULL) && (!item_maior(item, atual->proximo->item))) break;

        atual = atual->proximo;

    }
    // terminou de deslocar para o próximo, verifica se o abaixo é nulo
    // se for nulo, chama a função novamente passando o nó debaixo como argumento
    if (atual->abaixo != NULL) {
        ultimo = lista_inserir(lista, item, atual->abaixo);
    }
    // se o nível atual for o mais abaixo (0) e o último for diferente de nulo, então é inserido o novo nessa posição
    if (atual->nivel == 0 || (ultimo != NULL)) {
        NO *new_node = (NO *) malloc(sizeof(NO));
        new_node->item = item;
        new_node->abaixo = ultimo;
        new_node->nivel = atual->nivel;
        new_node->proximo = atual->proximo;
        atual->proximo = new_node;
        // se a randomização que tem 50% de chance retornar 1 e não for o nível mais alto, retorna o novo nó para 
        // inserir um nível acima
        if (randomizacao() && (atual->nivel < MAX_LEVEL - 1)) {
            return new_node;
        }
    }

    return NULL;

}

int lista_alterar(LISTA *lista, char *palavra, char *significado) { 
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


// função recursiva utilizada para remover um nó
void recursao_remover(LISTA *lista, ITEM *item, NO *anterior) {
    // cria-se um nó cabeça que será possível acessar posteriormente
    NO *cabeca_emergencia = anterior;
    // anda para o próximo enquanto ele for menor que o que se quer achar para remover
    while (anterior->proximo != NULL && !item_igual(item, anterior->proximo->item)) {
        anterior = anterior->proximo;
    }
    // se andou e chegou a ser nulo o próximo sem achar, volta para repetir o processo para o nó abaixo
    // da cabeça armazenada no começo
    if (anterior->proximo == NULL && cabeca_emergencia->abaixo != NULL) {
        recursao_remover(lista, item, cabeca_emergencia->abaixo);
    // senão, realiza-se a remoção
    } else if ((anterior->proximo != NULL) && item_igual(item, anterior->proximo->item)) {
        NO *tmp = anterior->proximo;
        anterior->proximo = tmp->proximo;
        if (anterior->abaixo == NULL) {
            item_apagar(&(tmp->item));
        }
        free(tmp);
        tmp = NULL;
        // se ainda houver níveis abaixo, a função é chamada para o nó anterior abaixo

        if (anterior->abaixo != NULL) {
            recursao_remover(lista, item, anterior->abaixo);
        } else {
        // se não houver níveis abaixo, apenas retorna
            return;
        }
        
    }



    
}




// apenas chama a função recursiva passando-se o nó cabeça na main
void lista_remover(LISTA *lista, ITEM *item, NO *atual) {
    recursao_remover(lista, item, atual);

}

// função que busca e retorna o item buscado na skiplist
ITEM *lista_busca(LISTA *lista, ITEM *item_to_search, NO *atual) {
    
    // se o próximo for igual, retorna ele
    if ((atual->proximo != NULL) && (atual->proximo->item != NULL) && item_igual(item_to_search, atual->proximo->item)) {
        return atual->proximo->item;
    }
    // terminou de mover

    // quebra se o próximo for nulo
    while (1) {
        if (atual->proximo == NULL) break;
    // se o próximo não for nulo e for igual, retorna ele
        if ((atual->proximo != NULL) && (atual->proximo->item != NULL) && item_igual(item_to_search, atual->proximo->item)) return atual->proximo->item;
    // senão, move para o próximo
        if ((atual->proximo != NULL) && (atual->proximo->item != NULL) && (!item_maior(item_to_search, atual->proximo->item))) break;

        atual = atual->proximo;

    }
    // se existirem níveis abaixo ainda, a função recursiva é chamada passando-se o nó abaixo como argumento
    if (atual->abaixo != NULL) {
        return lista_busca(lista, item_to_search, atual->abaixo);
    } else {
    // senão, retorna-se NULL
        return NULL;
    }
}

// imprime todas as palavras que iniciam com a letra passada, assim como seus significados
void lista_imprimir(LISTA *lista, char c){  
    NO* primeiro;

    // caso não seja encontrada nenhuma palavra com a letra desejada, o aviso é impresso
    if((primeiro = lista_busca_caracter(lista, c)) == NULL){
        printf("NAO HA PALAVRAS INICIADAS POR %c\n", c);
        return;
    }

    // caso contrário, são impressas as palavras e seus significados que começam com a letra desejada
    while (primeiro != NULL && item_get_palavra(primeiro->item)[0] == c) {
        printf("%s %s\n", item_get_palavra(primeiro->item), item_get_significado(primeiro->item));
        primeiro = primeiro->proximo;
    }

}

// função que busca a primeira palavra com o caractere passado (possui lógica similar a da busca)
NO* lista_busca_caracter(LISTA *lista, char c) {
    if (!lista || !lista->cabeca) {
        return NULL;
    }

    NO *analisado = lista->cabeca;

    while (analisado) {
        // se o próximo não é nulo
        if (analisado->proximo != NULL) {
            // define-se um char que recebe o primeiro caractere da próxima palavra
            char next_char = item_get_palavra(analisado->proximo->item)[0];
            // se esse caractere for menor que o procurado, anda para o próximo
            if (next_char < c) {
                analisado = analisado->proximo;
                // se o próximo caractere for igual, então verifica-se se não é o último nível
            } else if (next_char == c) {
                // se não for, o analisado recebe o analisado abaixo (que seria o anterior)
                if (analisado->abaixo != NULL) {
                    analisado = analisado->abaixo;
                    // se for o último nível, ele é retornado (precisa ser o último nível debaixo para imprimir todas)
                } else {
                    return analisado->proximo;
                }
            } else {
                analisado = analisado->abaixo;
            }
        } else {
            analisado = analisado->abaixo;
        }
    }

    return NULL;
}


// função que apagará todos os nós e itens da lista, assim como a cabeça e o ponteiro para ela
int lista_apagar(LISTA **lista) {
    if (*lista == NULL) {
        return 1; // Lista já está vazia
    }

    // nó atual recebe a cabeça
    NO* atual = (*lista)->cabeca;
    while (atual != NULL) {

        // cria-se um nó que será o próximo ao horizontal
        NO* horizontal = atual;
        while (horizontal != NULL) {
            NO* proximo = horizontal->proximo;

            // se o nível for o mais abaixo, o item pode ser apagado (apagamos o item apenas uma vez para cada)
            if (horizontal->nivel == 0 && proximo) {
                item_apagar(&(proximo->item));
            }

            // se o próximo não é nulo, libera-se esse nó
            if(proximo) {
                horizontal->proximo = proximo->proximo;
                free(proximo);
            } else {
                horizontal = NULL;
            }
        }
        // cria-se um nó temporário que recebe o atual (era um elemento da cabeça)
        NO* tmp = atual;

        // o atual recebe o debaixo (cabeça do nível abaixo)
        atual = atual->abaixo;

        // libera-se a memória do temporário
        free(tmp);
    }

    // libera-se o ponteiro para a lista e ela recebe NULL
    free(*lista);
    *lista = NULL; 

    return 0; 
}


// função que retorna se não há nada na lista
int lista_vazia(LISTA *lista) {
    if(lista->cabeca == NULL) return 1;
    return 0;
}

// função que retorna caso não de para alocar mais nós (ou seja, está cheia)
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
