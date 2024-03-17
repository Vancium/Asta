#pragma once
#include "../../Core.h"
#include "../../Util/Logger/Logger.h"
#include "../../Util/Memory/Memory.h"

enum {
    VECTOR_CAPACITY,
    VECTOR_LENGTH,
    VECTOR_STRIDE,
    VECTOR_FIELD_LENGTH
};

void *_vector_create( u64 length, u64 stride );

void _vector_destroy( void *vec );

u64 _vector_get_field( void *vec, u64 field );
void _vector_set_field( void *vec, u64 field, u64 value );

void *_vector_resize( void *vec );

void *_vector_push( void *vec, const void *valPtr );
void _vector_pop( void *vec, void *dest );

void *_vector_pop_at( void *vec, u64 index, void *dest );
void *_vector_insert_at( void *vec, u64 index, void *valPtr );

#define VECTOR_DEFAULT_CAPACITY 1
#define VECTOR_RESIZE_FACTOR 2

#define vector_create( type ) _vector_create( VECTOR_DEFAULT_CAPACITY, sizeof( type ) )

#define vector_reserve( type, capacity ) _vector_Create( capacity, sizeof( type ) )

#define vector_destroy( vec ) _vector_destroy( vec )

#define vector_push( vec, val )           \
    {                                     \
        typeof( val ) temp = val;         \
        vec = _vector_push( vec, &temp ); \
    }

#define vector_pop( vec, valPtr ) _vector_pop( vec, valPtr )

#define vector_pop_at( vec, index, valPtr ) _vector_pop_at( vec, index, valPtr )

#define vector_clear( vec ) _vector_set_field( vec, VECTOR_LENGTH, 0 )

#define vector_capacity( vec ) _vector_get_field( vec, VECTOR_CAPACITY )

#define vector_length( vec ) _vector_get_field( vec, VECTOR_LENGTH )

#define vector_stride( vec ) _vector_get_field( vec, VECTOR_STRIDE )
#define vector_set_length( vec, val ) _vector_set_field( vec, VECTOR_LENGTH, val )
