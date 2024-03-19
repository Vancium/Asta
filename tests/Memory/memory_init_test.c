#include "Asta/Util/Memory/Memory.h"
#include <Asta.h>

int main( void ) {

    MemorySystem *memsys;

    memsys = memory_system_init();

    for ( int i = 0; i < MAX_MEMORY_TAG; i++ ) {
        if ( memsys->allocatedTags[ i ] != 0 ) {
            return 1;
        }
    }

    if ( memsys->totalAllocations != 0 ) {
        return 1;
    }

    free( memsys );
    return 0;
}
