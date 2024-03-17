#pragma once

#include "../../Core.h"

enum LogLevel {
    LOG_FATAL,
    LOG_ERROR,
    LOG_WARN,
    LOG_DEBUG,
    LOG_INFO,
    LOG_TRACE,
};

enum LoggerType { CORE,
                  GAME } LoggerType;

//@breif Initialize file logger
void logger_init();
//@breif Logs message to standard output stream
//@param -> enum LogLevel level : Log level for the output message
//@param -> enum LoggerType type : Logger type, either CORE or GAME
//@param -> const char* msg : Output message for logger, formated with variadic arguments if present
//@param -> ... : optional arguments to format into output string
AAPI void log_message( enum LogLevel level, enum LoggerType type, const char *msg, ... );

//@breif Terminate file logger
void logger_terminate();

#define LOG_CORE_FATAL( msg, ... ) log_message( LOG_FATAL, CORE, msg, ##__VA_ARGS__ )
#define LOG_CORE_ERROR( msg, ... ) log_message( LOG_ERROR, CORE, msg, ##__VA_ARGS__ )
#define LOG_CORE_WARN( msg, ... ) log_message( LOG_WARN, CORE, msg, ##__VA_ARGS__ )
#define LOG_CORE_DEBUG( msg, ... ) log_message( LOG_DEBUG, CORE, msg, ##__VA_ARGS__ )
#define LOG_CORE_INFO( msg, ... ) log_message( LOG_INFO, CORE, msg, ##__VA_ARGS__ )
#define LOG_CORE_TRACE( msg, ... ) log_message( LOG_TRACE, CORE, msg, ##__VA_ARGS__ )

#define LOG_GAME_FATAL( msg, ... ) log_message( LOG_FATAL, GAME, msg, ##__VA_ARGS__ )
#define LOG_GAME_ERROR( msg, ... ) log_message( LOG_ERROR, GAME, msg, ##__VA_ARGS__ )
#define LOG_GAME_WARN( msg, ... ) log_message( LOG_WARN, GAME, msg, ##__VA_ARGS__ )
#define LOG_GAME_DEBUG( msg, ... ) log_message( LOG_DEBUG, GAME, msg, ##__VA_ARGS__ )
#define LOG_GAME_INFO( msg, ... ) log_message( LOG_INFO, GAME, msg, ##__VA_ARGS__ )
#define LOG_GAME_TRACE( msg, ... ) log_message( LOG_TRACE, GAME, msg, ##__VA_ARGS__ )
