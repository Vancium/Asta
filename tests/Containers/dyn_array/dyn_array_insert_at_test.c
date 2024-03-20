
#include "Asta/Util/Logger/Logger.h"
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

    u64 *header = (u64 *)arr - DYN_ARRAY_MAX_FIELD;

    u64 i_length = header[ DYN_ARRAY_LENGTH_FIELD ];
    u64 i_capacity = header[ DYN_ARRAY_CAPACITY_FIELD ];
    u64 stride = header[ DYN_ARRAY_STRIDE_FIELD ];

    int target_x = 13423523;
    int target_y = 32425435;
    int target_index = 1;
    struct TestData target_data = {
        .x = target_x,
        .y = target_y,
    };

    int i_target_x = arr[ target_index ].x;
    int i_target_y = arr[ target_index ].y;

    arr = _dyn_array_insert_at( arr, &target_data, 1, memsys );

    if ( arr[ target_index ].x != target_x || arr[ target_index ].y != target_y ) {
        return 1;
    }

    if ( arr[ target_index + 1 ].x != i_target_x || arr[ target_index + 1 ].y != i_target_y ) {
        LOG_CORE_FATAL( "%i", arr[ target_index + 1 ] );
        LOG_CORE_FATAL( "%i", i_target_x );
    }

    return 0;
}
