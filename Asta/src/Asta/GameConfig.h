#pragma once
#include <stdbool.h>
#include "Core.h"

typedef struct Game {

    bool ( *init )( struct Game *game );

    void *State;
} Game;
