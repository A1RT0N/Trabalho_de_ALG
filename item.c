#include "item.h"

struct item_{ 
  char palavra[50];
  char significado[140];
};

ITEM *item_criar(char palavra[], char significado[]){

  ITEM *item;

  item = (ITEM *) malloc(sizeof(ITEM));
    
  if (item != NULL){

    strcpy(item->palavra, palavra);

    strcpy(item->significado, significado);

    return(item);
  }

  return(NULL);
}

int item_apagar(ITEM **item){
   if (*item != NULL){
      free (*item);
      *item = NULL; 
      return(1);
   }
   return(0);
}

char* item_get_palavra(ITEM *item){
  if (item != NULL)
    return(item->palavra);
}

char* item_get_significado(ITEM *item){
  if (item != NULL) 
    return(item->significado);
}


int item_set_palavra(ITEM *item, char *palavra){
  if (item != NULL){
      strcpy(item->palavra, palavra);
      return (1);
  }
  return (0);
}


int item_set_significado(ITEM *item, char *significado){

  if (item != NULL){
      strcpy(item->significado, significado);
      return (1);
  }
  return (0);
}

void item_imprimir(ITEM *item){
  if (item != NULL)
    printf("%s %s\n", item->palavra, item->significado);
}


int item_maior(ITEM* item_novo, ITEM* item){
  if(strcmp(item_get_palavra(item_novo), item_get_palavra(item)) > 0){
    return 1;
  }

  return 0;
}

int item_igual(ITEM* item_novo, ITEM* item){
  if(strcmp(item_get_palavra(item_novo), item_get_palavra(item)) == 0){
    return 1;
  }

  return 0;
}