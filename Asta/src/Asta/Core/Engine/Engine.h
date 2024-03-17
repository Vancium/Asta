#pragma once

#include "../../Core.h"

typedef struct EngineConfig {
    char *name;
    u32 width;
    u32 height;
} EngineConfig_t;

typedef struct Engine {
    EngineConfig_t config;
} Engine_t;

AAPI Engine_t *engine_init( EngineConfig_t engineConfig );

AAPI void engine_terminate( Engine_t *engine );
