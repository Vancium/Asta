#pragma once

#include "../Core.h"
#include "Asta/Util/Memory/Memory.h"

typedef struct Renderer {

} Renderer;

Renderer *renderer_create( MemorySystem *memsys );

void renderer_preprare( Renderer *renderer, MemorySystem *memsys );

void renderer_update( Renderer *renderer, MemorySystem *memsys );

void renderer_destroy( Renderer *self, MemorySystem *memsys );
