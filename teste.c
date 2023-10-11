#include "item.h"

int main(){

    char palavra[7] = "palavra";
    char significado[11] = "significado";

    printf("oi");

    ITEM *item = item_criar(palavra, significado);

    char palavra2[8] = "palavra2";
    char significado2[12] = "significado2";

    ITEM* item_novo = item_criar(palavra2, significado2);

    printf("%s", item_get_palavra(item));

    printf("Imprimir depois de mudar : \n");

    

    item_set_palavra(item_novo, significado2);
    item_set_significado(item_novo, palavra2);

    printf("%s", item_get_palavra(item));

    printf("Imprimir item com significado: \n");

    item_imprimir(item);


    
    return 0;
}