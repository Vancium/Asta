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

    // Check that header values are set correctly
    u64 *header = (u64 *)arr - DYN_ARRAY_MAX_FIELD;

    u64 length = header[ DYN_ARRAY_LENGTH_FIELD ];
    u64 capacity = header[ DYN_ARRAY_CAPACITY_FIELD ];
    u64 stride = header[ DYN_ARRAY_STRIDE_FIELD ];

    int test_x = 32545345;

    int test_y = 234235645;
    struct TestData test_data = {
        .x = test_x,
        .y = test_y,
    };

    arr = _dyn_array_push( arr, &test_data, memsys );
    if ( arr[ 0 ].x != test_x ) {
        return 1;
    }

    struct TestData popped_data;

    _dyn_array_pop( arr, &popped_data, memsys );

    if ( popped_data.x != test_x ) {
        return 1;
    }

    if ( popped_data.y != test_y ) {
        return 1;
    }

    return 0;
}
