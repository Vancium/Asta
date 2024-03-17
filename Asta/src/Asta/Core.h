#pragma Eonce

#include "Util/Logger/Logger.h"
#include "Util/Memory/Memory.h"

#include <stdint.h>
#include <stdbool.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef float f32;
typedef double f64;

#if defined( __clang__ ) || defined( __GNUC__ )
/** @brief Static assertion */
#    define STATIC_ASSERT _Static_assert
#else

/** @brief Static assertion */
#    define STATIC_ASSERT static_assert
#endif

#ifdef AS_PLATFORM_MACOS
#    define AAPI __attribute__( ( visibility( "default" ) ) )
#else
#    define AAPI
#endif
