
#pragma once

#include "../../Core.h"

struct EventContext {
    // 128 bytes
    union {
        i64 i64[ 2 ];
        u64 u64[ 2 ];
        f64 f64[ 2 ];

        i32 i32[ 4 ];
        u32 u32[ 4 ];
        f32 f32[ 4 ];

        i16 i16[ 8 ];
        u16 u16[ 8 ];

        i8 i8[ 16 ];
        u8 u8[ 16 ];

        char c[ 16 ];
    } data;
};

enum EventCodes {
    EVENT_CODE_APPLICATION_QUIT = 0x01,
    EVENT_CODE_KEY_PRESSED = 0x02,
    EVENT_CODE_KEY_RELEASED = 0x03,
    EVENT_CODE_MOUSE_BUTTON_PRESSED = 0x04,
    EVENT_CODE_MOUSE_BUTTON_RELEASED = 0x05,
    EVENT_CODE_MOUSE_MOVED = 0x06,
    EVENT_CODE_MOUSE_SCROLLED = 0x07,
    EVENT_CODE_WINDOW_RESIZED = 0x08,
    EVENT_CODE_FRAMEBUFFER_RESIZE = 0x09,
    MAX_EVENT_CODE = 0xFF
};

typedef bool ( *OnEventFn )( u16 code, void *sender, void *listener_inst, struct EventContext data );

bool event_system_init();
void event_system_destroy();

bool event_register( u16 code, void *listner, OnEventFn onEvent );

bool event_unregister( u16 code, void *listner, OnEventFn onEvent );

bool event_fire( u16 code, void *sender, struct EventContext context );
