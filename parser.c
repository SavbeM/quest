#include <stdio.h>
#include "parser.h"
#include <string.h>
#include <regex.h>
#include <stdlib.h>

struct parser* create_parser(){
    struct parser* parser = calloc(1, sizeof(struct parser));

    parser->history = calloc(1, sizeof(struct container));
    parser->commands = calloc(1, sizeof(struct container));

    parser->commands =  create_container(NULL, COMMAND, create_command("KONIEC", "Ends the game", "\\s*KONIEC\\s*", 1));
    create_container(parser->commands, COMMAND, create_command("SEVER", "Move to the room in the north", "\\s*SEVER\\s*", 1));
    create_container(parser->commands, COMMAND, create_command("JUH", "Move to the room in the south", "\\s*JUH\\s*", 1));
    create_container(parser->commands, COMMAND, create_command("VYCHOD", "Move to the room in the east", "\\s*VYCHOD\\s*", 1));
    create_container(parser->commands, COMMAND, create_command("ZAPAD", "Move to the room in the west", "\\s*ZAPAD\\s*", 1));
    create_container(parser->commands, COMMAND, create_command("ROZHLIADNI SA", "Look around the room", "\\s*ROZHLIADNI SA\\s*", 1));
    create_container(parser->commands, COMMAND, create_command("PRIKAZY", "List all commands", "\\s*PRIKAZY\\s*", 1));
    create_container(parser->commands, COMMAND, create_command("VERZIA", "Show game version", "\\s*VERZIA\\s*", 1));
    create_container(parser->commands, COMMAND, create_command("RESTART", "Restart the game", "\\s*RESTART\\s*", 1));
    create_container(parser->commands, COMMAND, create_command("O HRE", "Show game introduction", "\\s*O HRE\\s*", 1));
    create_container(parser->commands, COMMAND, create_command("VEZMI", "Take an item", "\\s*VEZMI(\\s*.*)?\\s*", 2));
    create_container(parser->commands, COMMAND, create_command("POLOZ", "Drop an item", "\\s*POLOZ(\\s*.*)?\\s*", 2));
    create_container(parser->commands, COMMAND, create_command("INVENTAR", "Show backpack content", "\\s*INVENTAR\\s*", 1));
    create_container(parser->commands, COMMAND, create_command("POUZI", "Use an item", "\\s*POUZI(\\s*.*)?\\s*", 2));
    create_container(parser->commands, COMMAND, create_command("PRESKUMAJ", "Examine an item", "\\s*PRESKUMAJ(\\s*.*)?\\s*", 2));
    create_container(parser->commands, COMMAND, create_command("NAHRAJ", "Load game state", "\\s*NAHRAJ(\\s*.*)?\\s*", 2));
    create_container(parser->commands, COMMAND, create_command("ULOZ", "Save game state", "\\s*ULOZ(\\s*.*)?\\s*", 2));



    return parser;
}

struct parser* destroy_parser(struct parser* parser){
    if(parser == NULL){
        return NULL;
    }
    destroy_containers(parser->history);
    destroy_containers(parser->commands);

    free(parser);
    return NULL;
}

struct command* parse_input(struct parser* parser, char* input){
    if(parser == NULL || input == NULL){
        return NULL;
    }
    struct container* current = parser->commands;
    while(current != NULL){
        struct command* cmd = current->command;
        if(cmd == NULL){
            current = current->next;
            continue;
        }
        regmatch_t matches[cmd->nmatch];
        if(regexec(&(cmd->preg), input, cmd->nmatch, matches, 0) == 0){
            for(size_t i = 0; i < cmd->nmatch; i++){
                size_t start = (size_t) matches[i].rm_so;
                size_t end = (size_t) matches[i].rm_eo;
                size_t length = end - start;
                if (cmd->groups[i] != NULL) {
                    free(cmd->groups[i]);
                }
                cmd->groups[i] = calloc(length + 1, sizeof(char));
                strncpy(cmd->groups[i], &input[start], length);
                cmd->groups[i][length] = '\0';
            }
            return cmd;
        }
        current = current->next;
    }
    return NULL;
}