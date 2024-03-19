
#include "Memory.h"
#include "Asta/Util/Logger/Logger.h"
#include <stdlib.h>
#include <string.h>

MemorySystem *memory_system_init() {
    LOG_CORE_INFO( "Initializing Memory System" );
    MemorySystem *memsys = (MemorySystem *)malloc( sizeof( MemorySystem ) );
    memset( memsys, 0, sizeof( MemorySystem ) );
    return memsys;
}

void *memory_allocate( u64 size, enum MemoryTags tag, MemorySystem *memsys ) {
    memsys->totalAllocations += size;
    memsys->allocatedTags[ tag ] += size;

    void *block = malloc( size );

    return block;
}

void memory_free( void *block, u64 size, enum MemoryTags tag, MemorySystem *memsys ) {

    memsys->totalAllocations -= size;
    memsys->allocatedTags[ tag ] -= size;

    free( block );
}

void *memory_zero( void *block, u64 size ) {
    return memset( block, 0, size );
}

void *memory_set( void *block, i32 value, u64 size ) {
    return memset( block, value, size );
}
void *memory_copy( void *dest, const void *source, u64 size ) {
    return memcpy( dest, source, size );
}

void memory_system_destroy( MemorySystem *memsys ) {
    // TODO:
    free( memsys );
    memsys = 0;
}

AAPI void memory_get_usage( MemorySystem *memsys ) {
    static char *memory_tag_strings[ MAX_MEMORY_TAG ] = {
        "UNKNOWN",
        "ENGINE",
        "PLATFORM",
        "EVENT",
    };

    LOG_CORE_DEBUG( "\t\tMemory Usage" );

    for ( int i = 0; i < MAX_MEMORY_TAG; i++ ) {
        LOG_CORE_DEBUG( "\t\t[%s] [%d]", memory_tag_strings[ i ], memsys->allocatedTags[ i ] );
    }
}
