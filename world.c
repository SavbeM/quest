#include "world.h"
#include <stdlib.h>
#include <stdio.h>

struct container *create_world() {



    struct room *room1 = create_room("The Entrance to the Dungeon",
                                     "This place looks like the mouth of a gigantic beast carved into the rock.\n"
                                     "The air here is cold and damp, and the silence is broken only by the distant screams echoing through the cavernous depths.\n"
                                     "At the entrance stands a big guard in leather armour, large and sullen. His eyes glow in the darkness, and he holds a massive axe in his hands.\n"
                                     "He blocks your path, demanding 300 bucks for passage into the dungeon. You can feel the threat emanating from him, and understand that without payment,\n"
                                     "you will not be allowed to pass. To the south, beyond the forest, you can see a small camp.\n"
                                     "In the corner of the entrance, you notice the skeleton of a dead warrior with shield in his hand, a sword still sticking out of its ribcage.\n"
                                     "A rusty, weathered nameplate reads \"Billy Herrington\"");
    struct room *room2 = create_room("The Camp",
                                     "The camp is a grim sight. A few dead bandits are scattered around. One of them has 200 bucks sticking out of his pocket.\n"
                                     "A troll that attacked the camp stands nearby, but it doesn't seem to notice you.");
    struct room *room3 = create_room("First level of the Dungeon",
                                     "The dungeon is dark and damp. The walls are covered in moss, and the air is thick with the smell of decay.\n"
                                     "Three torches flicker in the gloom, casting long, dancing shadows. One torch marks the entrance to the east, another to the west, their light barely piercing the blackness beyond.\n"
                                     "The third torch burns near a wall, its flame illuminating an oddity in the stonework.\n"
                                     "On the wall, you see an inscription in an ancient language: \"He who seeks to survive must first seek the light. Take it, and a new path will reveal itself. For those who accepted the light, the road to the west.\"");
    struct room *room4 = create_room("The Hall of the Living",
                                     "The hall is filled with an eerie silence, broken only by the occasional drip of water from the ceiling. In the center of the room,\n"
                                     "illuminated by a single shaft of light from above, sits an old warrior. His armor is worn and battered, and his eyes hold the weight of countless battles.\n"
                                     "He tells you a tale of a legendary hero, Billy Herrington, who was once the master of this dungeon.\n"
                                     "The hero, he says, donned the leather armor found in The Hall of the Dead. The old warrior then teaches you a spell, a battle cry to be exact. He instructs you to stick your fingers and shout the cry. This, he assures you, will give you the strength to defeat the monster.\n"
                                     "  ");
    struct room *room5 = create_room("The Hall of the Dead",
                                     "The hall is filled with the stench of death. The walls are lined with the bones of fallen warriors, their armor rusted and broken.\n"
                                     "In the center of the room, you see a suit of leather armor, its surface marred by countless battles. The armor seems to call out to you, whispering of the power it holds.\n"
                                     "The armor is old and battered, but you can sense the strength within it.\n"
                                     " ");
    struct room *room6 = create_room("The Hall of the Masters",
                                     "This hall, once a place of honor and respect, now stands as a shadow of its former glory.\n"
                                     "The grandeur of the past can still be seen in the faded tapestries hanging on the walls, the ornate, albeit worn-out, furniture scattered around the room, and the remnants of intricate murals depicting ancient battles.\n"
                                     "In the center of the hall stands a large, black, muscular warrior. In his hand, he holds a mighty weapon, a bone sword engraved with the word \"boner\". His  leather armor, adorned with intricate silver designs, covers only a small part of his body, revealing his intimidating physique. His eyes, burning with a fierce determination, are fixed on you. Seeing you in the armor of the ancient hero, the warrior's eyes flash with a challenge. It's clear that he won't let you leave without a fight. The air in the room grows heavy with anticipation, the silence only broken by the warrior's steady breathing and the distant echo of your own heartbeat.\n"
                                     "     ");

    struct container *world = world = add_room_to_world(NULL, room1);
    add_room_to_world(world, room2);
    add_room_to_world(world, room3);
    add_room_to_world(world, room4);
    add_room_to_world(world, room5);
    add_room_to_world(world, room6);

    set_exits_from_room(room1, room3, room2, NULL, NULL);
    set_exits_from_room(room2, room1, NULL, NULL, NULL);
    set_exits_from_room(room3, room6, room1, room5, room4);

    struct item *sword = create_item("Sword", "A sharp and shiny sword", EXAMINABLE | MOVABLE);
    struct item *shield = create_item("Shield", "A sturdy wooden shield", EXAMINABLE | MOVABLE);
    struct item *bucks200 = create_item("200 bucks", "A stack of 200 bucks", EXAMINABLE | MOVABLE);
    struct item *torchEast = create_item("Torch from east entrance", "A torch marking the east entrance", EXAMINABLE);
    struct item *torchWest = create_item("Torch from west entrance", "A torch marking the west entrance", EXAMINABLE);
    struct item *torchNorth = create_item("Torch from north entrance", "A torch marking the north entrance",
                                          EXAMINABLE);
    struct item *battleCry = create_item("Battle Cry", "A powerful battle cry taught by the old warrior",
                                         USABLE | EXAMINABLE);
    struct item *leatherArmor = create_item("Leather Armor", "Old and battered leather armor",
                                            USABLE | EXAMINABLE | MOVABLE);

    add_item_to_room(room1, sword);
    add_item_to_room(room1, shield);
    add_item_to_room(room2, bucks200);
    add_item_to_room(room3, torchEast);
    add_item_to_room(room3, torchWest);
    add_item_to_room(room3, torchNorth);
    add_item_to_room(room4, battleCry);
    add_item_to_room(room5, leatherArmor);


    for (int i = 7; i <= 15; i++) {
        char room_name[30];
        char room_description[100];
        sprintf(room_name, "Room %d", i);
        sprintf(room_description, "This is room number %d", i);
        struct room *room = create_room(room_name, room_description);
        add_room_to_world(world, room);

        char item_name[30];
        char item_description[100];
        sprintf(item_name, "Item %d", i);
        sprintf(item_description, "This is item number %d", i);
        struct item *item = create_item(item_name, item_description, EXAMINABLE | MOVABLE);
        add_item_to_room(room, item);

        struct room *north = get_room(world, "Room 1");
        struct room *south = get_room(world, "Room 2");
        struct room *east = get_room(world, "Room 3");
        struct room *west = get_room(world, "Room 4");
        set_exits_from_room(room, north, south, east, west);
    }

    return world;
}

struct container *add_room_to_world(struct container *world, struct room *room) {
    if (room == NULL){
        return NULL;
    }
    if(get_room(world, room->name) != NULL){
        return NULL;
    }
    struct container* new_room = NULL;

    if (world == NULL) {
        world = create_container(NULL, ROOM, room);
    } else {
      new_room = create_container(world, ROOM, room);
    }

    return new_room ? new_room : world;
}

struct container *destroy_world(struct container *world) {
    if (world == NULL) {
        return NULL;
    }

    destroy_containers(world);
    world = NULL;
    return NULL;
}

struct room *get_room(struct container *world, char *name) {
    if (world == NULL || name == NULL) {
        return NULL;
    }


    return get_from_container_by_name(world, name);
}
