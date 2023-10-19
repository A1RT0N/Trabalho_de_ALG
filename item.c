#include "item.h"
// struct item conterá palavra e seu significado, com as quantidades predefinidas de caracteres cada um
struct item_{ 
  char palavra[50];
  char significado[140];
};
// item criar aloca espaço para o item
ITEM *item_criar(char palavra[], char significado[]){

  ITEM *item;

  item = (ITEM *) malloc(sizeof(ITEM));
  // se conseguiu alocar, palavra e significado recebem os parâmetros palavra e significado
  if (item != NULL){

    strcpy(item->palavra, palavra);

    strcpy(item->significado, significado);

    return(item);
  }
// caso contrário, retorna NULL
  return(NULL);
}

// item apagar libera o item e define seu ponteiro como NULL
int item_apagar(ITEM **item){
   if (*item != NULL){
      free (*item);
      *item = NULL; 
      return(1);
   }
   return(0);
}

// retorna a palavra do item
char* item_get_palavra(ITEM *item){
  if (item != NULL)
    return(item->palavra);
}

// retorna o significado do item
char* item_get_significado(ITEM *item){
  if (item != NULL) 
    return(item->significado);
}

// altera a palavra do item para a nova palavra passada
int item_set_palavra(ITEM *item, char *palavra){
  if (item != NULL){
      strcpy(item->palavra, palavra);
      return (1);
  }
  return (0);
}

// altera o significado da palavra para o significado passado
int item_set_significado(ITEM *item, char *significado){

  if (item != NULL){
      strcpy(item->significado, significado);
      return (1);
  }
  return (0);
}

// imprime a palavra e seu significado em seguida, separados por um espaço
void item_imprimir(ITEM *item){
  if (item != NULL)
    printf("%s %s\n", item->palavra, item->significado);
}

// verifica se a palavra dos dois items é a mesma, se for retorna 1, senão, retorna 0
int item_igual(ITEM *item1, ITEM *item2) {
  if (strcmp(item_get_palavra(item1), item_get_palavra(item2)) == 0) {
    return 1;
  }
  return 0;
}

// verifica se a primeira palavra é "maior" que a segunda, ou seja, "vem depois" na tabela ASCII letra a letra
// caso a primeira seja maior, retorna 1, caso contrário, retorna 0
int item_maior(ITEM* item_novo, ITEM* item){
  if(strcmp(item_get_palavra(item_novo), item_get_palavra(item)) > 0){
    return 1;
  }

  return 0;
}