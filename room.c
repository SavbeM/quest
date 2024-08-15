#include "room.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define EXIT_SIZE 4
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

struct room* create_room(char *name, char *description){

    if(name == NULL || description == NULL){
        fprintf(stderr, "Incorrect description or name.\n");
        return NULL;
    }

    if(strlen(name) == 0 || strlen(description) == 0){
        fprintf(stderr, "Incorrect description or name.\n");
        return NULL;
    }

    struct room* room = calloc(1, sizeof(struct room));
    room->name = calloc(strlen(name) + 1, sizeof (char));
    room->description = calloc(strlen(description) + 1, sizeof (char));
    strcpy(room->name, name);
    strcpy(room->description, description);
    room->north = NULL;
    room->south = NULL;
    room->east = NULL;
    room->west = NULL;
    room->items = NULL;

    return room;
}

struct room* destroy_room(struct room* room){
    if(room == NULL){
        fprintf(stderr,"Cannot destroy NULL. \n");
        return NULL;
    }

    struct room* ptr;

    if(room->east != NULL){
        ptr = room->east;
        ptr->west = NULL;
    }

    if (room->west != NULL){
        ptr = room->west;
        ptr->east  = NULL;
    }

    if(room->north != NULL){
        ptr = room->north;
        ptr->south = NULL;
    }

    if(room->south != NULL){
        ptr = room->south;
        ptr->north = NULL;
    }

    if(room->items != NULL) {
        destroy_containers(room->items);
        room->items = NULL;
    }
    free(room->name);
    room->name = NULL;
    free(room->description);
    room->description = NULL;
    free(room);
    room = NULL;

    return room;
}

void set_exits_from_room(struct room *room, struct room *north, struct room *south, struct room *east, struct room *west){
    if(room == NULL){
        fprintf(stderr, "Cannot create exits for NULL room");
        return;
    }

    if(north != NULL){
        room->north = north;
        if(north->south == NULL){
            north->south = room;
        }
    }

    if(south != NULL){
        room->south = south;
        if(south->north == NULL){
            south->north = room;
        }
    }

    if(west != NULL){
        room->west = west;
        if(west->east == NULL){
            west->east = room;
        }
    }

    if(east != NULL){
        room->east = east;
        if(east->west == NULL){
            east->west = room;
        }
    }
    return;
}

void show_room(const struct room* room){
    if(room == NULL){
        fprintf(stderr, "Ja vas ne zval, idite nahui\n");
        return;
    }
    printf( ANSI_COLOR_RED"You are in %s\n\n", room->name);
    printf( ANSI_COLOR_RESET"%s\n\n", room->description);

    if(room->items != NULL){
        printf(ANSI_COLOR_YELLOW "You see: \n");
           struct container* ptr = room->items;
        while (ptr != NULL){
                printf(ANSI_COLOR_MAGENTA"%s\n", ((struct item*)ptr->item)->name);
            ptr = ptr->next;
        }
    }

    printf(ANSI_COLOR_BLUE "You can go: \n");
    if(room->east)  printf(ANSI_COLOR_CYAN"East to %s\n", room->east->name);
    if(room->west)  printf(ANSI_COLOR_CYAN"West to %s\n", room->west->name);
    if(room->north)  printf(ANSI_COLOR_CYAN"North to %s\n", room->north->name);
    if(room->south)  printf(ANSI_COLOR_CYAN"South to %s\n", room->south->name);
}

void delete_item_from_room(struct room* room, struct item* item){
    if(room == NULL || item == NULL){
        fprintf(stderr, "Incorrect data of item to delete from room");
        return;
    }

    room->items = remove_container(room->items, item);
}

void add_item_to_room(struct room* room, struct item* item){
    if(room == NULL || item == NULL){
        fprintf(stderr, "Incorrect data of item to add in room");
        return;
    }

    if(room->items == NULL) {
        room->items = create_container(NULL, ITEM, item);
    } else {
        create_container(room->items, ITEM ,item);
    }
}
struct item* get_item_from_room(const struct room* room, const char* name){
    if(room == NULL || name == NULL){
        fprintf(stderr, "Incorrect data cant get data from room");
        return NULL;
    }

    return get_from_container_by_name(room->items, name);
}
