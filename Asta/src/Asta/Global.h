#pragma once

#include "Core/Engine/Engine.h"
#include "Core/Window/Window.h"

struct Global {
    Engine_t *engine;
    Window_t *window;
};

extern struct Global global;
