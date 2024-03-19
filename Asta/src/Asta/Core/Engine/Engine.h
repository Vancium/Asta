#pragma once
#include "../../Core.h"
#include "../../GameConfig.h"
#include "../Platform/Platform.h"
#include "../../Renderer/Renderer.h"
#include "Asta/Util/Memory/Memory.h"

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
    Renderer *renderer;
} Engine;

bool engine_create( Engine *e, Game *game, MemorySystem *memsys );

bool init_glfw();

bool init_glad();

bool engine_run( Engine *e, MemorySystem *memsys );

bool engine_destroy( Engine *e, MemorySystem *memsys );
