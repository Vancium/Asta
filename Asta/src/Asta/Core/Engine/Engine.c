#include <stdlib.h>
#include "Engine.h"
#include "Asta/Core/Window/Window.h"
#include "Asta/Global.h"
#include "Asta/Util/Memory/Memory.h"

Engine_t *engine_init( EngineConfig_t engineConfig ) {

    memory_init();
    Engine_t *engine = allocate_memory( sizeof( Engine_t ), MEMORY_TAG_APPLICATION );
    engine->config = engineConfig;

    LOG_CORE_INFO( "Engine Created" );
    return engine;
}

void engine_terminate( Engine_t *engine ) {
    LOG_CORE_INFO( "Engine Destroyed" );
    get_memory_usage();
    memory_shutdown();
    free_memory( engine, sizeof( Engine_t ), MEMORY_TAG_APPLICATION );
}
