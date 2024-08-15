#include "command.h"
#include <stdlib.h>
#include "regex.h"
#include <stdio.h>
#include <string.h>

struct command *create_command(char *name, char *description, char *pattern, size_t nmatch) {

    if(name == NULL || description == NULL){
        return NULL;
    }

    if(strlen(name) == 0 || strlen(description) == 0){
        return NULL;
    }

    if(pattern != NULL){
        if(strlen(pattern) == 0 || nmatch <= 0){
            return NULL;
        }
    }
    struct command *command = calloc(1, sizeof(struct command));
    command->name = calloc(50, sizeof(char));
    command->description = calloc(250, sizeof (char));

    strcpy(command->name , name);
    strcpy(command->description, description);

    if(pattern != NULL) {
        regcomp(&(command->preg), pattern, REG_EXTENDED | REG_ICASE);

        command->nmatch = nmatch;
        command->groups = calloc(nmatch, sizeof(char *));
        for (size_t i = 0; i < nmatch; ++i) {
            command->groups[i] = calloc(50, sizeof(char));
        }
    }

    return command;
}

struct command* destroy_command(struct command* command){
    if(command == NULL){
        fprintf(stderr, "Cannot destroy NULL command");
        return NULL;
    }
    if (command->nmatch > 0) {
        for (size_t i = 0; i < command->nmatch; ++i) {
            free(command->groups[i]);
        }
    }
    free(command->groups);
    free(command->name);
    free(command->description);
    regfree(&(command->preg));
    free(command);

    return NULL;
}