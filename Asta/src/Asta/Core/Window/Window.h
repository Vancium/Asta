#pragma once
#include "../../Core.h"
#include <GLFW/glfw3.h>
typedef struct Window {
    GLFWwindow *handle;
    u32 width;
    u32 height;
} Window_t;

Window_t *window_create( u32 width, u32 height, char *name );

void window_destroy( Window_t *self );
