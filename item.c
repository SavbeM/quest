#include "item.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct item* create_item(char* name, char* description, unsigned int properties){
    if(name == NULL || description == NULL){
        fprintf(stderr, "Cannot create new item, incorrect name or description");
        return NULL;
    }

    if(strlen(name) == 0 || strlen(description) == 0){
        return NULL;
    }

    struct item* item = calloc(1, sizeof (struct item));

    item->name = calloc(50, sizeof(char));
    item->description = calloc(250, sizeof(char));
    strcpy(item->name, name);
    strcpy(item->description, description);
    item->properties = properties ? properties : 0;


    return item;
}

struct item* destroy_item(struct item* item){
    if(item == NULL){
        fprintf(stderr, "Cannot destroy NULL item");
        return NULL;
    }

    free(item->name);
    free(item->description);
    free(item);

    return NULL;
}