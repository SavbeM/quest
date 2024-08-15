#include "backpack.h"
#include <stdlib.h>

struct backpack* create_backpack(const int capacity){
    if(capacity <= 0){
        return NULL;
    }
    struct backpack* bp = calloc(1, sizeof(struct backpack));
    bp->capacity = capacity;
    bp->size = 0;
    bp->items = NULL;
    return bp;
}

struct backpack* destroy_backpack(struct backpack* backpack){
    if(backpack == NULL){
        return NULL;
    }
    if(backpack->items != NULL) {
        destroy_containers(backpack->items);
        free(backpack->items);
    }
    free(backpack);
    return NULL;
}

bool add_item_to_backpack(struct backpack* backpack, struct item* item){
    if(backpack == NULL || item == NULL){
        return false;
    }
    if(backpack->size >= backpack->capacity){
        return false;
    }
    if(backpack->items == NULL){
        backpack->items = create_container(NULL, ITEM, item);
    }
    else {
        create_container(backpack->items, ITEM, item);
    }
    backpack->size++;
    return true;
}

void delete_item_from_backpack(struct backpack* backpack, struct item* item){
    if(backpack == NULL || item == NULL){
        return;
    }
    remove_container(backpack->items, item);
    backpack->size--;
}

struct item* get_item_from_backpack(const struct backpack* backpack, char* name){
    if(backpack == NULL || name == NULL){
        return NULL;
    }
    return get_from_container_by_name(backpack->items, name);
}