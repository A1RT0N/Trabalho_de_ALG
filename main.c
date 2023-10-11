#include "item.h"
#include "lista.h"

int main(){

    srand((unsigned int)time(NULL)); // PRECISA DESSE CARA PRA GERAR ALEATÓRIA

    char palavra[7] = "palavra";
    char significado[11] = "significado";

    printf("oi");

    ITEM *item = item_criar(palavra, significado);

    LISTA* lista = lista_criar();

    lista_inserir(lista, item);

    
    
    
    return 0;
}