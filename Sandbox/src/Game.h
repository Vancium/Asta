#pragma once
#include <Asta.h>

typedef struct GameState {
    f32 deltaTime;
} GameState_t;

bool game_init( Game *game );
