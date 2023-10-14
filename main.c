#include "item.h"
#include "lista.h"

int main(){

    srand((unsigned int)time(NULL));

    LISTA *dicionario;
    dicionario = lista_criar();

    char instrucao[10];

    char * palavra = (char *) malloc(50);
    char * significado = (char *) malloc(140);

    while (1) {
        scanf("%s ", instrucao);

        if (strcmp(instrucao, "insercao") == 0) {
        
            char * palavra2 = (char *) malloc(50);
            char * significado2 = (char *) malloc(140);
            scanf(" %s ", palavra);
            scanf(" %[^\n]", significado);
            strcpy(palavra2,palavra);
            strcpy(significado2,significado);
            ITEM *nova_palavra;
            nova_palavra = item_criar(palavra2, significado2);
            lista_inserir(dicionario, nova_palavra);
        
        }
        else if (strcmp(instrucao, "alteracao") == 0) {
            printf("oi");

            char * palavra3 = (char *) malloc(50);
            char * signidicado3 = (char *) malloc(140);
            scanf(" %s", palavra);
            scanf(" %[^\n]", significado);
            strcpy(palavra3,palavra);
            strcpy(signidicado3,significado);
            printf("Bem antes");
            // lista_alterar(dicionario, palavra, significado); 

        }
        else if (strcmp(instrucao, "remocao") == 0) {

            char * palavra4 = (char *) malloc(50);
            scanf(" %s", palavra);
            strcpy(palavra4,palavra);
            lista_remover(dicionario, palavra);
        }

        else if (strcmp(instrucao, "busca") == 0) {

            char * palavra5 = (char *) malloc(50);
            scanf("%s", palavra);
            strcpy(palavra5,palavra);
            ITEM *item;
            item = item_criar(palavra5, "");
            ITEM *resultado = lista_busca(dicionario, item);
            if (resultado != NULL) {
                item_imprimir(resultado);
            } else {
                printf("Palavra não encontrada\n");
            }

        }
        else if (strcmp(instrucao, "impressao") == 0) {

            char c;
            scanf(" %c", &c);
            lista_imprimir(dicionario, c);
        }
        else if(strcmp(instrucao, "imprimir") == 0){
            imprimir_lista(dicionario);
        }

        else if (strcmp(instrucao, "sair") == 0) {
            lista_apagar(&dicionario);
            break;
        }

    }
    
    return 0;
}