
#include "Window.h"
#include "../../Util/Logger/Logger.h"
#include "Asta/Util/Memory/Memory.h"
#include "GLFW/glfw3.h"
#include <stdlib.h>

Window_t *window_create( u32 width, u32 height, char *name ) {
    // Window *win = malloc( sizeof( Window ) );
    Window_t *self = allocate_memory( sizeof( Window_t ), MEMORY_TAG_WINDOW );
    // Initialize glfw

    if ( !glfwInit() ) {
        LOG_CORE_FATAL( "GLFW could not be initialized" );
        exit( 1 );
    }

    // Configure GLFW

    self->width = width;
    self->height = height;

    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 1 );
    glfwWindowHint( GLFW_CLIENT_API, GLFW_NO_API );

    self->handle = glfwCreateWindow( self->width, self->height, name, NULL, NULL );

    // GLFW Event callbacks

    glfwMakeContextCurrent( self->handle );

    return self;
}

AAPI void window_destroy( Window_t *self ) {

    glfwDestroyWindow( self->handle );

    self->handle = NULL;

    free_memory( self, sizeof( Window_t ), MEMORY_TAG_WINDOW );
}
