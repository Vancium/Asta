
#include "vector.h"

void *_vector_create( u64 length, u64 stride ) {
    u64 headerSize = VECTOR_FIELD_LENGTH * sizeof( u64 );
    u64 vectorSize = length * stride;
    u64 *newVector = allocate_memory( headerSize + vectorSize, MEMORY_TAG_VECTOR );
    set_memory( newVector, 0, headerSize + vectorSize );

    newVector[ VECTOR_CAPACITY ] = length;
    newVector[ VECTOR_LENGTH ] = 0;
    newVector[ VECTOR_STRIDE ] = stride;
    return (void *)( newVector + VECTOR_FIELD_LENGTH );
}

void _vector_destroy( void *vec ) {
    u64 *header = (u64 *)vec - VECTOR_FIELD_LENGTH;
    u64 headerSize = VECTOR_FIELD_LENGTH * sizeof( u64 );
    u64 totalSize = headerSize + header[ VECTOR_CAPACITY ] * header[ VECTOR_STRIDE ];
    free_memory( header, totalSize, MEMORY_TAG_VECTOR );
}

u64 _vector_get_field( void *vec, u64 field ) {

    u64 *header = (u64 *)vec - VECTOR_FIELD_LENGTH;
    return header[ field ];
}
void _vector_set_field( void *vec, u64 field, u64 value ) {

    u64 *header = (u64 *)vec - VECTOR_FIELD_LENGTH;
    header[ field ] = value;
}

void *_vector_resize( void *vec ) {
    u64 length = vector_length( vec );
    u64 stride = vector_stride( vec );
    void *temp = _vector_create( ( VECTOR_RESIZE_FACTOR * vector_capacity( vec ) ), stride );
    copy_memory( temp, vec, length * stride );

    _vector_set_field( temp, VECTOR_LENGTH, length );
    _vector_destroy( vec );
    return temp;
}
void *_vector_push( void *vec, const void *valPtr ) {
    u64 length = vector_length( vec );
    u64 stride = vector_stride( vec );

    if ( length >= vector_capacity( vec ) ) {
        vec = _vector_resize( vec );
    }

    u64 addr = (u64)vec;
    addr += ( length * stride );
    copy_memory( (void *)addr, valPtr, stride );
    _vector_set_field( vec, VECTOR_LENGTH, length + 1 );
    return vec;
}
void _vector_pop( void *vec, void *dest ) {
    u64 length = vector_length( vec );
    u64 stride = vector_stride( vec );

    u64 addr = (u64)vec;
    addr += ( ( length - 1 ) * stride );
    copy_memory( dest, (void *)addr, stride );
    _vector_set_field( vec, VECTOR_LENGTH, length - 1 );
}

void *_vector_pop_at( void *vec, u64 index, void *dest ) {
    u64 length = vector_length( vec );
    u64 stride = vector_stride( vec );
    if ( index >= length ) {
        LOG_CORE_ERROR( "Index out of bounds for vector: Length: %i, index: %index", length, index );
        return vec;
    }

    u64 addr = (u64)vec;
    copy_memory( dest, (void *)( addr + ( index * stride ) ), stride );
    if ( index != length - 1 ) {
        copy_memory( (void *)( addr + ( index * stride ) ), (void *)( addr + ( ( index + 1 ) * stride ) ), stride * ( length - index ) );
    }

    _vector_set_field( vec, VECTOR_LENGTH, length - 1 );
    return vec;
}
void *_vector_insert_at( void *vec, u64 index, void *valPtr ) {
    u64 length = vector_length( vec );
    u64 stride = vector_stride( vec );
    if ( index >= length ) {
        LOG_CORE_ERROR( "Index out of bounds for vector: Length: %i, index: %index", length, index );
        return vec;
    }
    if ( length >= vector_capacity( vec ) ) {
        vec = _vector_resize( vec );
    }

    u64 addr = (u64)vec;

    if ( index != length - 1 ) {
        copy_memory( (void *)( addr + ( index + 1 * stride ) ), (void *)( addr + ( index * stride ) ), stride * ( length - index ) );
    }

    copy_memory( (void *)( addr + ( index * stride ) ), valPtr, stride );
    _vector_set_field( vec, VECTOR_LENGTH, length + 1 );
    return vec;
}
