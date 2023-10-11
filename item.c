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

bool item_apagar(ITEM **item){
   if (*item != NULL){
      free (*item);
      *item = NULL; 
      return(true);
   }
   return(false);
}

char* item_get_palavra(ITEM *item){
  if (item != NULL)
    return(item->palavra);
}


bool item_set_palavra(ITEM *item, char palavra[]){
  if (item != NULL){
      for(int i = 0; i < 50; i++){
        item->palavra[i] = palavra[i];
      }
      return (true);
  }
  return (false);
}


bool item_set_significado(ITEM *item, char significado[]){

  if (item != NULL){
      for(int i = 0; i < 300; i++){
        item->significado[i] = significado[i];
      }
      return (true);
  }
  return (false);
}

void item_imprimir(ITEM *item){
  if (item != NULL)
    printf("%s: %s\n", item->palavra, item->significado);
}


bool item_maior(ITEM* item_novo, ITEM* item){
  if(strcmp(item_get_palavra(item_novo), item_get_palavra(item)) > 0){
    return true;
  }

  return false;
}
