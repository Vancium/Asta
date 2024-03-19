#pragma once
#include "../../Core.h"
#include "../../GameConfig.h"
#include "../Platform/Platform.h"

typedef struct EngineConfig {
    u32 width;
    u32 height;
    char *name;
    bool running;
} EngineConfig;

typedef struct Engine {
    Game *game;
    EngineConfig config;
    Platform *platform;
} Engine;

bool engine_create( Engine *e, Game *game, MemorySystem *memsys );

bool init_glfw();

bool engine_run( Engine *e );

bool engine_destroy( Engine *e, MemorySystem *memsys );
