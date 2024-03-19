#include "Asta/Util/Memory/Memory.h"
#include <Asta.h>

int main( void ) {

    char target_value = 'g';

    u32 size = 10;

    char *test_array = (char *)malloc( sizeof( char ) * size );
    char *target_array = (char *)malloc( sizeof( char ) * size );

    for ( int i = 0; i < size; i++ ) {

        test_array[ i ] = target_value;
    }

    memory_set( target_array, target_value, size );

    for ( int i = 0; i < size; i++ ) {
        if ( target_array[ i ] != test_array[ i ] ) {
            return 1;
        }
    }
    return 0;
}
