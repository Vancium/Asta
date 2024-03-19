#include "Renderer.h"
#include <OpenGL/OpenGL.h>
#include <glad/glad.h>

Renderer *renderer_create( MemorySystem *memsys ) {
    Renderer *self = memory_allocate( sizeof( Renderer ), MEMORY_TAG_UNKNOWN, memsys );
    AASSERT_MSG( self != NULL, "Failed to allocate memory for renderer" );

    return self;
}

void renderer_preprare( Renderer *renderer, MemorySystem *memsys ) {
    glClearColor( 0.5f, 0.2f, 0.7f, 1.0f );
}

void renderer_update( Renderer *renderer, MemorySystem *memsys ) {
    glClear( GL_COLOR_BUFFER_BIT );
}

void renderer_destroy( Renderer *self, MemorySystem *memsys ) {

    memory_free( self, sizeof( Renderer ), MEMORY_TAG_UNKNOWN, memsys );
}
