
#include "Memory.h"
#include "../Logger/Logger.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// TODO implement memory alignment

struct MemoryStatistics {
    u64 totalAllocated;
    u64 taggedAllocations[ MEMORY_MAX_TAG ];
};

static const char *memoryTagStrings[ MEMORY_MAX_TAG ] = {
    "UNKNOWN",
    "VECTOR",
    "APPLICATION",
    "WINDOW",
    "RENDERER" };

static struct MemoryStatistics stats;

void memory_init() {
    memset( &stats, 0, sizeof( stats ) );
}
void memory_shutdown() {
}

//@breif allocates `size` amount of memory on the heap
//@param size:
//          unsigned 64 bit integer representing how much memory to allocate
//@param tag:
//          enum value of
void *allocate_memory( u64 size, enum MemoryTags tag ) {
    if ( tag == MEMORY_TAG_UNKNOWN ) {
        LOG_CORE_WARN( "allocateMemory() called with MEMORY_TAG_UNKNOWN. Re-class this allocation" );
    }

    stats.totalAllocated += size; // add size in bytes to totalAllocated
    stats.taggedAllocations[ tag ] += size;

    void *block = malloc( size );
    memset( block, 0, sizeof( block ) );
    return block;
}

//@breif frees `size` amount of memory from the heap
//@param block:
//          void pointer representing the address that was returned from allocate memory
//@param size:
//          unsigned 64 bit integer representing how much memory to free
//@param tag:
//          enum value of
void free_memory( void *block, u64 size, enum MemoryTags tag ) {
    if ( tag == MEMORY_TAG_UNKNOWN ) {
        LOG_CORE_WARN( "allocateMemory() called with MEMORY_TAG_UNKNOWN. Re-class this allocation" );
    }

    stats.totalAllocated -= size; // add size in bytes to totalAllocated
    stats.taggedAllocations[ tag ] -= size;

    free( block );
}

void *zero_memory( void *block, u64 size ) {
    return memset( block, 0, size );
}
void *copy_memory( void *dest, const void *source, u64 size ) {
    return memcpy( dest, source, size );
}
void *set_memory( void *dest, i32 value, u64 size ) {
    return memset( dest, value, size );
}

char *get_memory_usage() {
    const u64 gib = (int)1024 * 1024 * 1024;
    const u64 mib = 1024 * 1024;
    const u64 kib = 1024;

    char buffer[ 8000 ] = "Tagged Memory Use:\n";

    u64 offset = strlen( buffer );

    for ( u32 i = 0; i < MEMORY_MAX_TAG; i++ ) {
        char unit[ 4 ] = "XiB";
        float amount = 1.0f;

        if ( stats.taggedAllocations[ i ] >= gib ) {
            unit[ 0 ] = 'G';
            amount = stats.taggedAllocations[ i ] / (float)gib;
        } else if ( stats.taggedAllocations[ i ] >= mib ) {
            unit[ 0 ] = 'M';
            amount = stats.taggedAllocations[ i ] / (float)mib;
        } else if ( stats.taggedAllocations[ i ] >= kib ) {
            unit[ 0 ] = 'K';
            amount = stats.taggedAllocations[ i ] / (float)kib;
        } else {
            unit[ 0 ] = 'B';
            unit[ 1 ] = 0;
            amount = (float)stats.taggedAllocations[ i ];
        }

        i32 length = snprintf( buffer + offset, 8000, "\t\t\t\t\t\t\t%s: %.2f%s\n", memoryTagStrings[ i ], amount, unit );

        offset += length;
    }

    char *outStr = strdup( buffer );
    return outStr;
}
