#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "world.h"
#include "room.h"
#include "game.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_VIOLET  "\x1b[35m"

struct game* create_game() {
    struct game *game =  calloc(1, sizeof(struct game));

    if (game == NULL) {
        return NULL;
    }

    game->state = PLAYING;
    game->parser = create_parser();
    game->world = create_world();
    game->backpack = create_backpack(10);

    game->current_room = game->world->room;


    return game;
}

struct game* destroy_game(struct game* game){
    if (game == NULL) {
        return NULL;
    }

    destroy_parser(game->parser);
    destroy_world(game->world);
    destroy_backpack(game->backpack);
    free(game);

    return NULL;
}

void play_game(struct game* game){
    if (game == NULL) {
        return;
    }

    printf(ANSI_COLOR_VIOLET "Welcome to the game!\n\n");
    printf(ANSI_COLOR_GREEN"You can use the following commands:\n\n");
    execute_command(game, parse_input(game->parser, "PRIKAZY"));
    show_room(game->current_room);

    do {
        printf(ANSI_COLOR_GREEN"What do you want to do?\n");
        printf(">");
        char input[INPUT_BUFFER_SIZE];
        fgets(input, INPUT_BUFFER_SIZE, stdin);

        struct command* command = parse_input(game->parser, input);
        execute_command(game, command);
    } while(game->state == PLAYING);

    if(game->state == RESTART){
        destroy_game(game);
        game = create_game();
        play_game(game);
    }
}



void execute_command(struct game* game, struct command* command){
    if (game == NULL || command == NULL) {
        return;
    }
    if (strcmp(command->name, "KONIEC") == 0){
        game->state = GAMEOVER;
    }
    else if(strcmp(command->name, "SEVER") == 0){
        if (game->current_room->north != NULL){
            game->current_room = game->current_room->north;
            show_room(game->current_room);
        }
        else{
            printf("You can't go there!\n");
        }
    }
    else if(strcmp(command->name, "VYCHOD") == 0){
        if (game->current_room->east != NULL){
            game->current_room = game->current_room->east;
            show_room(game->current_room);
        }
        else{
            printf("You can't go there!\n");
        }
    }
    else if(strcmp(command->name, "JUH") == 0){
        if (game->current_room->south != NULL){
            game->current_room = game->current_room->south;
            show_room(game->current_room);
        }
        else{
            printf("You can't go there!\n");
        }
    }
    else if(strcmp(command->name, "ZAPAD") == 0){
        if (game->current_room->west != NULL){
            game->current_room = game->current_room->west;
            show_room(game->current_room);
        }
        else{
            printf("You can't go there!");
        }
    }
    else if(strcmp(command->name, "ROZHLIADNI SA") == 0){
        get_room(game->world, game->current_room->name);
        show_room(game->current_room);
    }
    else if(strcmp(command->name, "VEZMI") == 0){
        if (command->groups[1] == NULL){
            printf("You need to specify what to take!\n");
            return;
        }
        if (command->groups[1] != NULL){
            if(strlen(command->groups[1]) < 3){
                printf("You need to specify what to take!\n");
                return;
            }
            char* itemName = command->groups[1];
            char* token = strtok(itemName, " \n");
            itemName = token != NULL ? token : itemName;
            struct item* itemFromRoom= get_item_from_room(game->current_room, itemName);
            if(itemFromRoom != NULL && itemFromRoom->properties & MOVABLE ){
                if (add_item_to_backpack(game->backpack, itemFromRoom)){
                    printf(ANSI_COLOR_VIOLET "You have picked %s.\n", itemFromRoom->name);
                    delete_item_from_room(game->current_room, itemFromRoom);
                }
            }
            else if(itemFromRoom != NULL && itemFromRoom->properties & ~(unsigned int)MOVABLE ){
                printf("You can't pick this item!\n");
            }
            else{
                printf("There is no such item in the room!\n");
                return;
            }
        }
        else{
            printf("There is nothing to take!\n");
        }
    }
    else if(strcmp(command->name, "PRIKAZY") == 0){
      struct container* current = game->parser->commands;
        while(current != NULL){
            struct command* cmd = current->command;
            if(cmd == NULL){
                current = current->next;
                continue;
            }
            printf("%s - %s\n\n", cmd->name, cmd->description);
            current = current->next;
        }
    }
    else if(strcmp(command->name, "VERZIA") == 0){
        printf("Game version: %f\n", 1.0);
    }
    else if(strcmp(command->name, "O HRE") == 0){
        printf("Welcome to the game!\n");
    }
    else if(strcmp(command->name, "INVENTAR") == 0){
        struct container* current = game->backpack->items;
        if(current == NULL){
            printf("Your backpack is empty!\n");
            return;
        }
        while(current != NULL){
            struct item* item = current->item;
            if(item == NULL){
                current = current->next;
                continue;
            }
            printf("Your items\n: %s - %s\n", item->name, item->description);
            current = current->next;
        }
    }
    else if(strcmp(command->name, "POUZI") == 0){
        if (command->groups[1] == NULL){
            printf("You need to specify what to use!\n");
            return;
        }
        if (command->groups[1] != NULL){
            struct item* itemFromBackpack = get_item_from_backpack(game->backpack, command->groups[1]);
            if(itemFromBackpack != NULL){
                delete_item_from_backpack(game->backpack,itemFromBackpack);
            }
            else{
                printf("There is no such item in the backpack!\n");
                return;
            }
        }
        else{
            printf("There is nothing to use!\n");
        }
    }
    else if(strcmp(command->name, "PRESKUMAJ") == 0) {
        if (command->groups[1] == NULL) {
            printf("You need to specify what to examine!\n");
            return;
        }
        if (command->groups[1] != NULL) {
            struct item *itemFromBackpack = get_item_from_backpack(game->backpack, command->groups[1]);
            if (itemFromBackpack != NULL) {
                printf("%s - %s", itemFromBackpack->name, itemFromBackpack->description);
            } else {
                printf("There is no such item in the backpack!\n");
                return;
            }
        }
    }
    else if(strcmp(command->name, "RESTART") == 0){
    game->state = RESTART;
    return;
    }
    else if(strcmp(command->name, "ULOZ") == 0){
        printf("Game saved!\n");
    }
    else if(strcmp(command->name, "NAHRAJ") == 0){
        printf("Game loaded!\n");
    }
    else{
        printf("Unknown command!\n");
    }
    return;
}