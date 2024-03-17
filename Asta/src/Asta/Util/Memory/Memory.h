#pragma once

#include "../../Core.h"

enum MemoryTags {
    MEMORY_TAG_UNKNOWN,
    MEMORY_TAG_VECTOR,
    MEMORY_TAG_APPLICATION,
    MEMORY_TAG_WINDOW,
    MEMORY_TAG_RENDERER,
    MEMORY_MAX_TAG
};

void memory_init();
void memory_shutdown();

void *allocate_memory( u64 size, enum MemoryTags tag );
void free_memory( void *block, u64 size, enum MemoryTags tag );

void *zero_memory( void *block, u64 size );
void *copy_memory( void *dest, const void *source, u64 size );
void *set_memory( void *dest, i32 value, u64 size );

AAPI char *get_memory_usage();
