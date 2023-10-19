#include "item.h"
#include "lista.h"

int main(){
    // srand iniciado para garantir a aleatoriedade ao chamar o rand (utilizado para gerar ou não níveis na skiplist)
    srand((unsigned int)time(NULL));
    // inicialização do dicionário
    LISTA *dicionario;
    dicionario = lista_criar();
    // inicialização de um char que coletará a instrução atual
    char instrucao[10];
    // inicialização de palavra e significado 
    char palavra[50];
    char significado[140];
    // loop para realizar as instruções (não há um número predefinido)
    while (1) {
        //leitura da instrução
        if (scanf(" %s ", instrucao) == EOF) break;
        if (strcmp(instrucao, "insercao") == 0) { 
            // se a instrução for insercao, coleta a palavra até o espaço e o significado até o \n
            char palavra2[50];
            char significado2[140];
            scanf(" %s ", palavra);
            scanf(" %[^\n]", significado);
            // palavra e significado são copiados para duas variáveis novas que serão usadas para criar o novo item do dicionário
            strcpy(palavra2,palavra);
            strcpy(significado2,significado);
            ITEM *nova_palavra;
            nova_palavra = item_criar(palavra2, significado2);
            lista_insercao(dicionario, nova_palavra);
        
        }
        else if (strcmp(instrucao, "alteracao") == 0) { 
            // definição de palavra e significado que serão utilizados
            char palavra3[50];
            char significado3[140];
            scanf(" %s", palavra);
            scanf(" %[^\n]", significado);
            strcpy(palavra3,palavra);
            strcpy(significado3,significado);
            if(lista_busca(dicionario, item_criar(palavra3, ""), cabeca(dicionario)) == 0){
                printf("OPERACAO INVALIDA\n");

            }else{
                (lista_alterar(dicionario, palavra, significado) == 0); 
            }
            // alteração do significado da palavra

        }
        else if (strcmp(instrucao, "remocao") == 0) { 
            // definição da palavra que será utilizada para remoção
            char palavra4[50];
            scanf(" %s", palavra);
            strcpy(palavra4, palavra);
            ITEM *palavra_remover = item_criar(palavra4, "");
            // se o item não estiver na lista, imprime que a operação é inválida
            if (lista_busca(dicionario, palavra_remover, cabeca(dicionario)) == 0){
                printf("OPERACAO INVALIDA\n");
                item_apagar(&palavra_remover);
            }
            else {
                lista_remover(dicionario, palavra_remover, cabeca(dicionario));
            }
        }


        else if (strcmp(instrucao, "busca") == 0) {
            // definição da palavra que será utilizada para a busca
            char palavra5[50];
            scanf("%s", palavra);
            strcpy(palavra5,palavra);
            ITEM *item;
            item = item_criar(palavra5, "");
            ITEM *resultado = lista_busca(dicionario, item, cabeca(dicionario));
            // se a busca for bem sucedida, imprime seu significado, senão imprime que a operação é inválida
            if (resultado != NULL) {
                printf("%s %s\n", item_get_palavra(resultado), item_get_significado(resultado));
            } else {
                printf("OPERACAO INVALIDA\n");
            }

        }

        // imprime todas as palavras que iniciam com o caractere passado
        else if (strcmp(instrucao, "impressao") == 0) {

            char c;
            scanf(" %c", &c);
            lista_imprimir(dicionario, c);
        }
        // essa função não foi pedida, mas foi usada para testar se a skiplist foi corretamente estruturada
        else if(strcmp(instrucao, "imprimir") == 0){
            imprimir_lista(dicionario);
        }

        else if (strcmp(instrucao, "sair") == 0) {
            lista_apagar(&dicionario);
            break;
        }

    }
    // lista é apagada
    lista_apagar(&dicionario);
    
    return 0;
}