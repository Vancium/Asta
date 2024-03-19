#include "Asta/Util/Memory/Memory.h"
#include "GLFW/glfw3.h"
#include <glad/glad.h>
#include "Platform.h"
#include "../../Util/Assert/Assert.h"

Platform *platform_create( u32 width, u32 height, char *name, MemorySystem *memsys ) {
    // TODO: memory subsystem
    Platform *self = memory_allocate( sizeof( Platform ), MEMORY_TAG_PLATFORM, memsys );

    self->width = width;
    self->height = height;

    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 1 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );

    self->window = glfwCreateWindow( self->width, self->height, name, NULL, NULL );
    AASSERT_MSG( self->window != NULL, "Failed to create glfw window" );

    glfwMakeContextCurrent( self->window );

    return self;
}

bool platform_destroy( Platform *platform, MemorySystem *memsys ) {

    glfwDestroyWindow( platform->window );

    memory_free( platform, sizeof( Platform ), MEMORY_TAG_PLATFORM, memsys );

    return true;
}
