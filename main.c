#include "container.h"
#include "game.h"
#include "parser.h"
#include "command.h"
#include "world.h"
#include "backpack.h"

#include "item.h"
#include "room.h"
#include <stdio.h>
#include <stdlib.h>


int main(){
    struct game* game = create_game();
    play_game(game);

    destroy_game(game);
    return 0;
}