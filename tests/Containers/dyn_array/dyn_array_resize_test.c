
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

    // Initial Meta data
    u64 *initial_mdata = (u64 *)arr - DYN_ARRAY_MAX_FIELD;

    u64 initial_capacity = initial_mdata[ DYN_ARRAY_CAPACITY_FIELD ];

    struct TestData *newArr = _dyn_array_resize( arr, memsys );

    // Meta data
    u64 *mdata = (u64 *)newArr - DYN_ARRAY_MAX_FIELD;

    u64 capacity = mdata[ DYN_ARRAY_CAPACITY_FIELD ];

    if ( capacity != ( initial_capacity * DYN_ARRAY_RESIZE_FACTOR ) ) {
        return 1;
    }

    return 0;
}
