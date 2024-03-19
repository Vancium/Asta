

#include <stdbool.h>
#include <Asta.h>

#include <Asta/EntryPoint.h>
#include "Asta/Util/Logger/Logger.h"
#include "Game.h"

bool create_game( Game *game ) {
    LOG_GAME_INFO( "Hello from the game" );
    game->init = game_init;

    return true;
}
