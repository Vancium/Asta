#include "Asta/Util/Memory/Memory.h"
#include <Asta.h>
#include <string.h>
struct TestStruct {
    int x;
    char *name;
};

int main( void ) {
    MemorySystem *memsys = (MemorySystem *)malloc( sizeof( MemorySystem ) );
    memset( memsys, 0, sizeof( MemorySystem ) );

    struct TestStruct *test = memory_allocate( sizeof( struct TestStruct ), MEMORY_TAG_UNKNOWN, memsys );

    if ( memsys->totalAllocations != sizeof( struct TestStruct ) ) {
        return 1;
    } else if ( memsys->allocatedTags[ MEMORY_TAG_UNKNOWN ] != sizeof( struct TestStruct ) ) {
        return 1;
    }
    return 0;
}
