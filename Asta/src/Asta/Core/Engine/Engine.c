#include "Engine.h"
#include "Asta/Core/Platform/Platform.h"
#include <GLFW/glfw3.h>
#include <stdbool.h>

bool init_glfw() {

    if ( !glfwInit() ) {
        // TODO: check for failure
        LOG_CORE_FATAL( "Could not initialize GLFW" );
        return false;
    }

    return true;
}

bool engine_create( Engine *e, Game *game, MemorySystem *memsys ) {
    // TODO: Get config info from user, mainly window size and window name
    e->game = game;
    e->config.name = "Asta";
    e->config.width = 1280;
    e->config.height = 720;
    e->config.running = true;

    if ( !init_glfw() ) {
        LOG_CORE_FATAL( "Could not initialze glfw" );
        return false;
    }

    e->platform = platform_create( e->config.width, e->config.height, e->config.name, memsys );

    return true;
}

bool engine_run( Engine *e ) {
    LOG_CORE_INFO( "Running" );

    while ( e->config.running ) {
        while ( !glfwWindowShouldClose( e->platform->window ) ) {
            glfwPollEvents();
        }
        e->config.running = false;
    }

    return true;
}

bool engine_destroy( Engine *e, MemorySystem *memsys ) {

    platform_destroy( e->platform, memsys );

    memory_free( e, sizeof( Engine ), MEMORY_TAG_ENGINE, memsys );

    return true;
}
