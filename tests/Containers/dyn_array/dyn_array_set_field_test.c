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

    u64 length = 11;

    _dyn_array_set_field( arr, DYN_ARRAY_LENGTH_FIELD, length );

    // Get meta data

    u64 *mdata = (u64 *)arr - DYN_ARRAY_MAX_FIELD;

    u64 arr_length = mdata[ DYN_ARRAY_LENGTH_FIELD ];

    if ( arr_length != length ) {
        return 1;
    }

    return 0;
}
