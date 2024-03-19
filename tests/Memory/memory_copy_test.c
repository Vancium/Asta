#include "Asta/Util/Memory/Memory.h"
#include <Asta.h>

int main( void ) {

    int size = 10;

    int *target_values = (int *)malloc( sizeof( int ) * size );
    int *test_values = (int *)malloc( sizeof( int ) * size );

    for ( int i = 0; i < size; i++ ) {
        target_values[ i ] = i + 1;
    }

    memory_copy( test_values, target_values, sizeof( int ) * size );

    for ( int i = 0; i < size; i++ ) {
        if ( target_values[ i ] != test_values[ i ] ) {
            return 1;
        }
    }
    return 0;
}
