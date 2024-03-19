
#include "Asta/Util/Memory/Memory.h"
#include <Asta.h>

int main( void ) {

    int size = 10;

    int *ptr = (int *)malloc( sizeof( int ) * size );

    for ( int i = 0; i < size; i++ ) {
        ptr[ i ] = i;
    }

    memory_zero( ptr, sizeof( int ) * size );

    for ( int i = 0; i < size; i++ ) {
        if ( ptr[ i ] != 0 ) {
            return 1;
        }
    }

    return 0;
}
