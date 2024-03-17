
#include "Event.h"

#include "../../Util/Memory/Memory.h"

#include "../../Containers/Vector/Vector.h"

struct RegisteredEvent {
    void *listener;
    OnEventFn callback;
};

struct EventCodeEntry {
    struct RegisteredEvent *events;
};

#define MAX_MESSAGE_CODES 16384

struct EventSystemState {
    struct EventCodeEntry registered[ MAX_MESSAGE_CODES ];
};

static bool initialized = false;
static struct EventSystemState EventSystem;

bool event_system_init() {
    if ( initialized == true ) {
        return false;
    }

    initialized = false;
    zero_memory( &EventSystem, sizeof( struct EventSystemState ) );
    initialized = true;
    return true;
}

void event_system_destroy() {
    for ( u16 i = 0; i < MAX_MESSAGE_CODES; i++ ) {
        if ( EventSystem.registered[ i ].events != 0 ) {
            vector_destroy( EventSystem.registered[ i ].events );
            EventSystem.registered[ i ].events = 0;
        }
    }
}

bool event_register( u16 code, void *listener, OnEventFn onEvent ) {
    if ( initialized == false ) {
        return false;
    }

    if ( EventSystem.registered[ code ].events == 0 ) {
        EventSystem.registered[ code ].events = vector_create( struct RegisteredEvent );
    }

    u64 registeredCount = vector_length( EventSystem.registered[ code ].events );

    // Check if event is registered
    for ( u64 i = 0; i < registeredCount; ++i ) {
        if ( EventSystem.registered[ code ].events[ i ].listener == listener ) {
            // TODO: warn
            return false;
        }
    }

    struct RegisteredEvent e;
    e.listener = listener;
    e.callback = onEvent;

    vector_push( EventSystem.registered[ code ].events, e );

    return true;
}

bool event_unregister( u16 code, void *listner, OnEventFn onEvent ) {
    if ( initialized == false ) {
        return false;
    }

    if ( EventSystem.registered[ code ].events == 0 ) {
        return false;
    }

    u64 registeredCount = vector_length( EventSystem.registered[ code ].events );

    for ( u64 i = 0; i < registeredCount; ++i ) {
        struct RegisteredEvent e = EventSystem.registered[ code ].events[ i ];

        if ( e.callback == onEvent && e.listener == listner ) {
            struct RegisteredEvent poppedEvent;
            vector_pop_at( EventSystem.registered[ code ].events, i, &poppedEvent );
            return true;
        }
    }
    return false;
}

bool event_fire( u16 code, void *sender, struct EventContext context ) {

    if ( initialized == false ) {
        return false;
    }

    // If nothing is registered for the code, boot out.
    if ( EventSystem.registered[ code ].events == 0 ) {
        return false;
    }

    u64 registeredCount = vector_length( EventSystem.registered[ code ].events );
    for ( u64 i = 0; i < registeredCount; ++i ) {
        struct RegisteredEvent e = EventSystem.registered[ code ].events[ i ];
        if ( e.callback( code, sender, e.listener, context ) ) {
            // Message has been handled, do not send to other listeners.
            return true;
        }
    }

    // Not found.
    return false;
}
