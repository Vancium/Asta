#pragma once

#include "../Core.h"
#include "Asta/Util/Memory/Memory.h"

enum DynArrayData {
    DYN_ARRAY_CAPACITY_FIELD,
    DYN_ARRAY_LENGTH_FIELD,
    DYN_ARRAY_STRIDE_FIELD,
    DYN_ARRAY_MAX_FIELD
};

//@breif Allocates memory for dynamic array
//@param initial capacity of dynamic array, default is 1
//@param length in bytes of indivdual data to be stored in dynamic array, defualt is 0
//@param pointer to memory subsystem
void *_dyn_array_init( u64 length, u64 stride, MemorySystem *memsys );

void _dyn_array_destroy( void *self, MemorySystem *memsys );

void *_dyn_array_resize( void *self, MemorySystem *memsys );

/*
 *
 * Utility functions for getting and setting dynamic arrays meta data
 *
 *
 */

void _dyn_array_set_field( void *self, u64 field, u64 value );

u64 _dyn_array_get_field( void *self, u64 field );

/*
 *
 *
 *
 *
 *
 */

void *_dyn_array_push( void *self, const void *value_ptr, MemorySystem *memsys );

void _dyn_array_pop( void *self, void *dest, MemorySystem *memsys );

void *_dyn_array_insert_at( void *self, const void *value_ptr, u64 index, MemorySystem *memsys );

void *_dyn_array_pop_at( void *self, void *dest, u64 index, MemorySystem *memsys );

#define DYN_ARRAY_DEFAULT_CAPACITY 1
#define DYN_ARRAY_RESIZE_FACTOR 2

// Dynamic array creation & destruction
#define dyn_array_init( type, memsys ) dyn_array_init( DYN_ARRAY_DEFAULT_CAPACITY, sizeof( type ), memsys )

#define dyn_array_reserve( type, capacity, memsys ) dyn_array_init( capacity, sizeof( type ), memsys )

#define dyn_array_destroy( self, memsys ) _dyn_array_destroy( self, memsys )
// Dynamic array field functions

#define dyn_array_length( self ) _dyn_array_get_field( self, DYN_ARRAY_LENGTH_FIELD )
#define dyn_array_capacity( self ) _dyn_array_get_field( self, DYN_ARRAY_CAPACITY_FIELD )
#define dyn_array_stride( self ) _dyn_array_get_field( self, DYN_ARRAY_STRIDE_FIELD )
