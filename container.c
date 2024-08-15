#include "container.h"
#include "ctype.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct container *find_last(struct container *first) {
    if (first == NULL) {
        fprintf(stderr, "Root node is NULL");
        return NULL;
    }
    struct container *ptr = first;
    if (ptr->next == NULL) {
        return ptr;
    }
    while (ptr->next != NULL) {
        ptr = ptr->next;
    }

    return ptr;
}


struct container *create_container(struct container *first, enum container_type type, void *entry) {
    if (entry == NULL) {
        fprintf(stderr, "Entry is NULL. \n");
        return NULL;
    }
    if (first != NULL && first->type != type) {
        fprintf(stderr, "Incorrect type. \n");
        return NULL;
    }
    struct container *container = calloc(1, sizeof(struct container));
    container->type = type;
    container->next = NULL;

    switch (type) {
        case ROOM:
            container->room = entry;
            break;
        case ITEM:
            container->item = entry;
            break;
        case COMMAND:
            container->command = entry;
            break;
        case TEXT:
            container->text = entry;
            break;
        default:
            free(container);
            return NULL;
    }

    if (first != NULL) {
        struct container* ptr= find_last(first);
        ptr->next = container;
    }

    return container;
}

struct container *destroy_containers(struct container *first) {
    if (first == NULL) {
        fprintf(stderr, "Nothing to free. Root node is NULL.\n");
        return NULL;
    }

    struct container *ptr = first;

    while (ptr != NULL) {
        switch (ptr->type) {
            case ROOM:
                destroy_room(ptr->room);
                break;
            case ITEM:
                destroy_item(ptr->item);
                break;
            case COMMAND:
                destroy_command(ptr->command);
                break;
            case TEXT:
                break;
            default:
                free(ptr->text);
                return NULL;
        }
        struct container *next = ptr->next;
        free(ptr);
        ptr = next;
    }
    return ptr;
}

int strcasecmp(const char *s1, const char *s2) {
    while (*s1 && (toupper((unsigned char)*s1) == toupper((unsigned char)*s2))) {
        s1++;
        s2++;
    }
    return toupper((unsigned char)*s1) - toupper((unsigned char)*s2);
}

void *get_from_container_by_name(struct container *first, const char *name) {
    if (first == NULL || name == NULL) {
        fprintf(stderr, "Incorrect search arguments.\n");
        return NULL;
    }

    struct container *ptr = first;
    void *result = NULL;

    while (ptr != NULL) {
        switch (ptr->type) {
            case ROOM:
                if (strcasecmp(ptr->room->name, name) == 0) {
                    result = ptr->room;
                }
                break;
            case ITEM:
                if (strcasecmp(ptr->item->name, name) == 0) {
                    result = ptr->item;
                }
                break;
            case COMMAND:
                if (strcasecmp(ptr->command->name, name) == 0) {
                    result = ptr->command;
                }
                break;
            case TEXT:
                if (strcasecmp(ptr->text, name) == 0) {
                    result = ptr->text;
                }
                break;
            default:
                break;
        }

        if (result != NULL) {
            break;
        }

        ptr = ptr->next;
    }
    
    return result;
}

struct container *remove_container(struct container *first, void *entry) {
    if (first == NULL || entry == NULL) {
        fprintf(stderr, "Incorrect remove parameters.\n");
        return NULL;
    }

    struct container *ptr = first;

    switch (ptr->type) {
        case ROOM:
            if (ptr->room == entry) {
                if(ptr->next != NULL) {
                    struct container *newroot = ptr->next;
                    free(ptr);
                    return newroot;
                } else {
                    free(ptr);
                    return NULL;
                }
            }
            break;
        case ITEM:
            if (ptr->item == entry) {
                    if (ptr->next != NULL) {
                        struct container *newroot = ptr->next;
                        free(ptr);
                        return newroot;
                    } else {
                        free(ptr);
                        return NULL;
                    }
            }
            break;
        case COMMAND:
            if (ptr->command == entry) {
                if(ptr->next != NULL) {
                    struct container *newroot = ptr->next;
                    free(ptr);
                    return newroot;
                } else {
                    free(ptr);
                    return NULL;
                }
            }
            break;
        case TEXT:
            if (ptr->text == entry) {
                if(ptr->next != NULL) {
                    struct container *newroot = ptr->next;
                    free(ptr);
                    return newroot;
                } else {
                    free(ptr);
                    return NULL;
                }
            }
            break;
        default:
            return NULL;
    }

    while (ptr->next != NULL) {
        switch (ptr->next->type) {
            case ROOM:
                if (ptr->next->room == entry) {
                    if(ptr->next->next != NULL) {
                        struct container *next = ptr->next;
                        ptr->next = ptr->next->next;
                        free(next);
                        next = NULL;
                    } else{
                        free(ptr->next);
                        ptr->next = NULL;
                    }
                    return first;
                }
                break;
            case ITEM:
                if (ptr->next->item == entry) {
                    struct container* next = ptr->next;
                    ptr->next = ptr->next->next;
                    next->next = NULL;
                    return first;
                }
                break;
            case COMMAND:
                if (ptr->next->command == entry) {
                    struct container* next = ptr->next;
                    ptr->next = ptr->next->next;
                    next->next = NULL;
                    return first;
                }
                break;
            case TEXT:
                if (strcmp(ptr->next->text, entry) == 0) {
                    struct container* next = ptr->next;
                    ptr->next = ptr->next->next;
                    next->next = NULL;
                    return first;
                }
                break;
            default:
                return NULL;
        }

        ptr = ptr->next;
    }
    return first;
}