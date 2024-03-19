#include "Engine.h"
#include "Asta/Renderer/Renderer.h"
#include "Asta/Util/Assert/Assert.h"
#include "Asta/Util/Logger/Logger.h"
#include "Asta/Util/Memory/Memory.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>

bool init_glfw() {

    if ( !glfwInit() ) {
        return false;
    }

    return true;
}

bool init_glad() {
    if ( !gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress ) ) {
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

    AASSERT_MSG( init_glfw(), "Could not initialize GLFW" );

    e->platform = platform_create( e->config.width, e->config.height, e->config.name, memsys );

    AASSERT_MSG( init_glad(), "Could not initialize GLAD" );

    e->renderer = renderer_create( memsys );

    return true;
}

bool engine_run( Engine *e, MemorySystem *memsys ) {
    LOG_CORE_INFO( "Running" );

    while ( e->config.running ) {
        while ( !glfwWindowShouldClose( e->platform->window ) ) {

            renderer_preprare( e->renderer, memsys );

            renderer_update( e->renderer, memsys );

            glfwPollEvents();

            glfwSwapBuffers( e->platform->window );
        }
        e->config.running = false;
    }

    return true;
}

bool engine_destroy( Engine *e, MemorySystem *memsys ) {

    platform_destroy( e->platform, memsys );

    renderer_destroy( e->renderer, memsys );

    memory_free( e, sizeof( Engine ), MEMORY_TAG_ENGINE, memsys );

    return true;
}
