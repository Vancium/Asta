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

    struct TestStruct *test = (struct TestStruct *)malloc( sizeof( struct TestStruct ) );
    memsys->totalAllocations += sizeof( struct TestStruct );
    memsys->allocatedTags[ MEMORY_TAG_UNKNOWN ] += sizeof( struct TestStruct );

    memory_free( test, sizeof( struct TestStruct ), MEMORY_TAG_UNKNOWN, memsys );

    if ( memsys->allocatedTags[ MEMORY_TAG_UNKNOWN ] != 0 ) {
        return 1;
    } else if ( memsys->totalAllocations != 0 ) {
        return 1;
    }
    return 0;
}
