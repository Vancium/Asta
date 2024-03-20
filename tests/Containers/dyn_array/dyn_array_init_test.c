#include "Asta/Util/Memory/Memory.h"
#include <Asta.h>

#include <Asta/Containers/dyn_array.h>

struct TestData {
    int x;
    int y;
};

int main( void ) {

    MemorySystem *memsys = memory_system_init();

    u64 test_stride = sizeof( struct TestData );

    struct TestData *arr = _dyn_array_init( 1, sizeof( struct TestData ), memsys );

    if ( arr == NULL ) {
        return 1;
    }

    // Stride of test data

    // Check that header values are set correctly

    u64 *header = (u64 *)arr - DYN_ARRAY_MAX_FIELD;

    u64 length = header[ DYN_ARRAY_LENGTH_FIELD ];
    u64 capacity = header[ DYN_ARRAY_CAPACITY_FIELD ];
    u64 stride = header[ DYN_ARRAY_STRIDE_FIELD ];

    if ( length != 0 ) {
        return 1;
    }

    if ( capacity != 1 ) {
        return 1;
    }

    if ( stride != test_stride ) {
        return 1;
    }

    return 0;
}
