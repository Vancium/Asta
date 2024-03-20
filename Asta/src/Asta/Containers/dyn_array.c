#include "dyn_array.h"
#include "Asta/Util/Logger/Logger.h"
#include "Asta/Util/Memory/Memory.h"

void *_dyn_array_init( u64 length, u64 stride, MemorySystem *memsys ) {
    u64 headerSize = DYN_ARRAY_MAX_FIELD * sizeof( u64 );
    u64 darraySize = length * stride;
    u64 *newDarray = memory_allocate( headerSize + darraySize, MEMORY_TAG_UNKNOWN, memsys );

    memory_set( newDarray, 0, headerSize + darraySize );

    newDarray[ DYN_ARRAY_CAPACITY_FIELD ] = length;
    newDarray[ DYN_ARRAY_LENGTH_FIELD ] = 0;
    newDarray[ DYN_ARRAY_STRIDE_FIELD ] = stride;

    // Returns only the memory of the data stored, not the meta data of the dynamic array
    return (void *)( newDarray + DYN_ARRAY_MAX_FIELD );
}

void _dyn_array_destroy( void *self, MemorySystem *memsys ) {
    // Get pointer of dynamic array meta data
    u64 *header = (u64 *)self - DYN_ARRAY_MAX_FIELD;

    // Get size of meta data
    u64 headerSize = DYN_ARRAY_LENGTH_FIELD * sizeof( u64 );

    // Total length in bytes of dynamic array and its meta data
    u64 totalSize = headerSize + header[ DYN_ARRAY_CAPACITY_FIELD ] * header[ DYN_ARRAY_STRIDE_FIELD ];

    memory_free( header, totalSize, MEMORY_TAG_UNKNOWN, memsys );
}

void *_dyn_array_resize( void *self, MemorySystem *memsys ) {
    // Get meta data
    u64 *mdata = (u64 *)self - DYN_ARRAY_MAX_FIELD;
    u64 length = mdata[ DYN_ARRAY_LENGTH_FIELD ];
    u64 stride = mdata[ DYN_ARRAY_STRIDE_FIELD ];
    u64 capacity = mdata[ DYN_ARRAY_CAPACITY_FIELD ];

    void *temp = _dyn_array_init( DYN_ARRAY_RESIZE_FACTOR * capacity, stride, memsys );

    memory_copy( temp, self, length * stride );

    _dyn_array_set_field( temp, DYN_ARRAY_LENGTH_FIELD, length );

    _dyn_array_destroy( self, memsys );

    return temp;
}

void _dyn_array_set_field( void *self, u64 field, u64 value ) {
    // Get meta data
    u64 *mdata = (u64 *)self - DYN_ARRAY_MAX_FIELD;

    mdata[ field ] = value;
}

u64 _dyn_array_get_field( void *self, u64 field ) {

    // Get meta data
    u64 *mdata = (u64 *)self - DYN_ARRAY_MAX_FIELD;

    return mdata[ field ];
}

void *_dyn_array_push( void *self, const void *value_ptr, MemorySystem *memsys ) {

    u64 *mdata = (u64 *)self - DYN_ARRAY_MAX_FIELD;

    u64 length = mdata[ DYN_ARRAY_LENGTH_FIELD ];
    u64 stride = mdata[ DYN_ARRAY_STRIDE_FIELD ];
    u64 capacity = mdata[ DYN_ARRAY_CAPACITY_FIELD ];

    if ( length >= capacity ) {
        self = _dyn_array_resize( self, memsys );
    }

    // address of begining of dynamic array
    u64 address = (u64)self;

    // address now points to next availble memory location
    address += ( length * stride );

    memory_copy( (void *)address, value_ptr, stride );

    _dyn_array_set_field( self, DYN_ARRAY_LENGTH_FIELD, length + 1 );
    return self;
}

void _dyn_array_pop( void *self, void *dest, MemorySystem *memsys ) {

    u64 *mdata = (u64 *)self - DYN_ARRAY_MAX_FIELD;

    u64 length = mdata[ DYN_ARRAY_LENGTH_FIELD ];
    u64 stride = mdata[ DYN_ARRAY_STRIDE_FIELD ];
    u64 capacity = mdata[ DYN_ARRAY_CAPACITY_FIELD ];

    // address of beginning of dynamic array
    u64 address = (u64)self;

    // address now points to the end of the array
    address += ( ( length - 1 ) * stride );

    memory_copy( dest, (void *)address, stride );

    _dyn_array_set_field( self, DYN_ARRAY_LENGTH_FIELD, length - 1 );
}

void *_dyn_array_insert_at( void *self, const void *value_ptr, u64 index, MemorySystem *memsys ) {

    u64 *mdata = (u64 *)self - DYN_ARRAY_MAX_FIELD;

    u64 length = mdata[ DYN_ARRAY_LENGTH_FIELD ];
    u64 stride = mdata[ DYN_ARRAY_STRIDE_FIELD ];
    u64 capacity = mdata[ DYN_ARRAY_CAPACITY_FIELD ];

    if ( index >= length ) {
        LOG_CORE_ERROR( "Index out of bound for dynamic array: Length: %i, index: %i", length, index );
        return self;
    }

    if ( length >= capacity ) {
        self = _dyn_array_resize( self, memsys );
    }

    u64 address = (u64)self;

    // Copy memory of self[index] to self[index+1]
    memory_copy(
        (void *)( address + ( index + 1 * stride ) ),
        (void *)( address + ( index * stride ) ),
        stride * ( length - index ) );

    // Copy memory of value_ptr into self[index]
    memory_copy( (void *)( address + ( index * stride ) ), value_ptr, stride );
    // Increment length of dynamic array
    _dyn_array_set_field( self, DYN_ARRAY_LENGTH_FIELD, length + 1 );
    return self;
}

void *_dyn_array_pop_at( void *self, void *dest, u64 index, MemorySystem *memsys ) {
    u64 *mdata = (u64 *)self - DYN_ARRAY_MAX_FIELD;

    u64 length = mdata[ DYN_ARRAY_LENGTH_FIELD ];
    u64 stride = mdata[ DYN_ARRAY_STRIDE_FIELD ];
    u64 capacity = mdata[ DYN_ARRAY_CAPACITY_FIELD ];

    if ( index >= length ) {
        LOG_CORE_ERROR( "Index out of bound for dynamic array: Length: %i, index: %i", length, index );
        return self;
    }

    u64 address = (u64)self;

    // Copy value to be popped into dest
    memory_copy( dest, (void *)( address + ( index * stride ) ), stride );

    if ( index != length - 1 ) {
        // Copy address of index + 1 into index
        memory_copy(
            (void *)( address + ( index * stride ) ),
            (void *)( address + ( ( index + 1 ) * stride ) ),
            stride * ( length - index ) );
    }
    _dyn_array_set_field( self, DYN_ARRAY_LENGTH_FIELD, length - 1 );
    return self;
}
