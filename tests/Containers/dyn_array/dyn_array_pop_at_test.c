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

    int test_x1 = 32545345;
    int test_y1 = 234235645;
    struct TestData test_data1 = {
        .x = test_x1,
        .y = test_y1,
    };

    int test_x2 = 32545345;
    int test_y2 = 234235645;
    struct TestData test_data2 = {
        .x = test_x2,
        .y = test_y2,
    };

    int test_x3 = 32545345;
    int test_y3 = 234235645;
    struct TestData test_data3 = {
        .x = test_x3,
        .y = test_y3,
    };

    arr = _dyn_array_push( arr, &test_data1, memsys );
    arr = _dyn_array_push( arr, &test_data2, memsys );
    arr = _dyn_array_push( arr, &test_data3, memsys );

    struct TestData target;

    u64 index = 1;

    u64 *header = (u64 *)arr - DYN_ARRAY_MAX_FIELD;

    u64 length = header[ DYN_ARRAY_LENGTH_FIELD ];
    u64 capacity = header[ DYN_ARRAY_CAPACITY_FIELD ];
    u64 stride = header[ DYN_ARRAY_STRIDE_FIELD ];

    arr = _dyn_array_pop_at( arr, &target, index, memsys );

    if ( target.x != test_x2 || target.y != test_y2 ) {
        return 1;
    }

    u64 *new_header = (u64 *)arr - DYN_ARRAY_MAX_FIELD;

    u64 new_length = header[ DYN_ARRAY_LENGTH_FIELD ];

    if ( new_length != length - 1 ) {
        return 1;
    }

    return 0;
}
