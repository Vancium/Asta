#pragma once
#include <stdbool.h>
#include "Asta/GameConfig.h"
#include "Asta/Util/Logger/Logger.h"
#include "Asta/Util/Memory/Memory.h"
#include "Core.h"
#include "Asta/Core/Engine/Engine.h"

extern bool create_game( Game *game );

int main( void ) {

    // Initialze Memory
    MemorySystem *memsys;

    memsys = memory_system_init();

    Game game;

    LOG_CORE_INFO( "Main Function" );

    if ( !create_game( &game ) ) {
        LOG_CORE_FATAL( "Could not create Game!" );
        return -1;
    }

    if ( !game.init ) {
        LOG_CORE_FATAL( "Game must have working function pointers" );
        return -2;
    }

    // Create Engine

    // TODO: Use memory subsystem
    Engine *e = memory_allocate( sizeof( Engine ), MEMORY_TAG_ENGINE, memsys );

    if ( !engine_create( e, &game, memsys ) ) {
        LOG_CORE_FATAL( "Could not initialze Engine" );
        return -3;
    }

    if ( !engine_run( e ) ) {
        LOG_CORE_FATAL( "Engine failed to run" );
        return -4;
    }

    engine_destroy( e, memsys );

    memory_get_usage( memsys );

    memory_system_destroy( memsys );
}
