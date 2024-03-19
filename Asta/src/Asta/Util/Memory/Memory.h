#pragma once

#include "../../Core.h"

enum MemoryTags {
    MEMORY_TAG_UNKNOWN,
    MEMORY_TAG_ENGINE,
    MEMORY_TAG_PLATFORM,
    MEMORY_TAG_EVENT,
    MAX_MEMORY_TAG
};

typedef struct MemorySystem {
    u64 totalAllocations;
    u64 allocatedTags[ MAX_MEMORY_TAG ];
} MemorySystem;

//@breif Initializes memory subsytem, allocates memory for struct MemorySystem and zeros the memory
//@return pointer to MemorySystem
MemorySystem *memory_system_init();

//@breif Frees memory allocated for MemorySystem memsys
void memory_system_destroy( MemorySystem *memsys );

//@breif Allocates memory of length (size)
//@param length of memory in bytes
//@param type of memory allocation
//@param pointer to memory system
//@return opaque pointer to allocated memory
void *memory_allocate( u64 size, enum MemoryTags tag, MemorySystem *memsys );

//@brief Zero's (block) of memory of length (size)
//@param opaque pointer to block of memory to be zero'd out
//@param length of memory in bytes
//@return opaque pointer to zerod out memory
void *memory_zero( void *block, u64 size );

//@brief For a block of memory of length (size), set's each byte to value
//@param opaque pointer to block of memory to be set
//@param value to set bytes to
//@param length of memory in bytes
void *memory_set( void *block, i32 value, u64 size );

//@breif Copies the first (size) bytes from source to the first (size) bytes of dest
//@param opaque pointer to destination memory
//@param upaque poitner to souce memory
//@param length of memory in bytes
void *memory_copy( void *dest, const void *source, u64 size );

//@breif
void memory_free( void *block, u64 size, enum MemoryTags, MemorySystem *memsys );

AAPI void memory_get_usage( MemorySystem *memsys );
