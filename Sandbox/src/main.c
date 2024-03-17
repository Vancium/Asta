
#include "Asta/Core/Window/Window.h"
#include "Asta/Util/Memory/Memory.h"
#include "GLFW/glfw3.h"
#include <stdio.h>
#include <Asta.h>

struct Global global;

int main( void ) {

    EngineConfig_t config = {
        .name = "Asta",
        .width = 1280,
        .height = 720,
    };

    global.engine = engine_init( config );

    global.window = window_create( global.engine->config.width, global.engine->config.height, global.engine->config.name );

    while ( !glfwWindowShouldClose( global.window->handle ) ) {
        glfwPollEvents();
    }

    window_destroy( global.window );
    LOG_GAME_INFO( "%s", get_memory_usage() );
    engine_terminate( global.engine );

    return 0;
}
