#pragma once

#include "../../Core.h"

#include "Asta/Util/Memory/Memory.h"
#include "GLFW/glfw3.h"

typedef struct Platform {
    GLFWwindow *window;
    u32 width;
    u32 height;
} Platform;

Platform *platform_create( u32 width, u32 height, char *name, MemorySystem *memsys );

bool platform_destroy( Platform *platform, MemorySystem *memsys );
