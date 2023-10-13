#include "item.h"
#include "lista.h"

int main(){

/*    srand((unsigned int)time(NULL)); // PRECISA DESSE CARA PRA GERAR ALEATÓRIA

    char palavra[7] = "palavra";
    char significado[11] = "significado";

    printf("oi");

    ITEM *item = item_criar(palavra, significado);

    LISTA* lista = lista_criar();

    lista_inserir(lista, item);
*/
    LISTA *dicionario;
    dicionario = lista_criar();

    // input que definirá qual função realizar naquele momento
    char instrucao[10];
    // um loop que voltará sempre a requisitar uma instrução, permitindo que um número não predefinido de instruções aconteça
    while (1) {
        scanf("%s", instrucao);

        if (strcmp(instrucao, "insercao") == 0) {
        
        // insercao str1 str2 : insere a palavra str1, com a definição str2, no dicionário;
        char *palavra;
        char *significado;
        palavra = (char *) malloc(50);
        significado = (char *) malloc(140);
        scanf(" %s", palavra);
        scanf(" %[^\n]", significado);
        ITEM *nova_palavra;
        nova_palavra = item_criar(palavra, significado);
        lista_inserir(dicionario, nova_palavra);
        
        }


        else if (strcmp(instrucao, "alteracao") == 0) {

        // alteracao str1 str2 : altera a definição da palavra str1 para str2;
        char *palavra;
        char *significado;
        palavra = (char *) malloc(50);
        significado = (char *) malloc(140);
        scanf(" %s", palavra);
        scanf(" %[^\n]", significado);
        lista_alterar(dicionario, palavra, significado); 

        }
        else if (strcmp(instrucao, "remocao") == 0) {

        // remocao str1 : remove a palavra str1 do dicionário;
        char *palavra;
        palavra = (char *) malloc(50);
        scanf(" %s", palavra);
        // lista_remover(dicionario, palavra); 

        }
        else if (strcmp(instrucao, "busca") == 0) {

        // busca str1 : imprime a definição da palavra str1;
        char *palavra;
        palavra = (char *) malloc(50);
        scanf(" %s", palavra);
        ITEM *buscado = item_criar(palavra, palavra);
        buscado = lista_busca(dicionario, buscado, MAX_LEVEL); 
        printf("%s\n", item_get_significado(buscado));

        }
        else if (strcmp(instrucao, "impressao") == 0) {

        // impressao ch1 : imprime todas as palavras iniciadas pelo caractere ch1 seguidas por suas respectivas
        // definições em ordem alfabética. Cada palavra (com sua respectiva definição) deve ser impresso em uma
        // linha diferente.  
        char c;
        // lista_imprimir(dicionario, c);

        }
    }   
    return 0;
}