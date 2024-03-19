#include "Logger.h"
#include <stdarg.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include "../../Core.h"

//@breif gets current time and sets the character string out to the formatted time D M Y 00:00:00
//@param -> char* out : character array to be set with the current time as a string
static void get_time( char *out ) {
    time_t rawTime;
    struct tm *timeInfo;
    time( &rawTime );
    timeInfo = localtime( &rawTime );

    sprintf( out, "%d %d %d %d:%d:%d", timeInfo->tm_mday, timeInfo->tm_mon + 1,
             timeInfo->tm_year + 1900, timeInfo->tm_hour, timeInfo->tm_min,
             timeInfo->tm_sec );
}
void logger_init() {
    // TODO: Initialize rotating file logger
}

void log_message( enum LogLevel level, enum LoggerType type, const char *msg, ... ) {
    static char *logLevelStrings[ 6 ] = { "FATAL", "ERROR", "WARN",
                                          "DEBUG", "INFO", "TRACE" };
    static char *logTypeStrings[ 2 ] = { "CORE", "APP" };
    static char *logLevelColors[ 6 ] = { "\e[1;91m", "\e[0;31m", "\e[1;93m",
                                         "\e[1;94m", "\e[1;97m", "\e[0;92m" };

    static const u16 MAX_LOG_MSG_LENGTH = 16000;

    char time[ 30 ];
    get_time( time );

    char outMessage[ MAX_LOG_MSG_LENGTH ];
    memset( outMessage, 0, sizeof( outMessage ) );

    va_list argPtr;
    va_start( argPtr, msg );
    vsnprintf( outMessage, MAX_LOG_MSG_LENGTH, msg, argPtr );
    va_end( argPtr );
    printf( "%s[%s] [%s] [%s] %s\n", logLevelColors[ level ], logTypeStrings[ type ],
            time, logLevelStrings[ level ], outMessage );
    printf( "\033[0m" );
}

void logger_terminate() {
    // TODO: Destroy rotating file logger
}

void report_assertion_failure( const char *expression, const char *message, const char *file, i32 line ) {
    log_message( LOG_FATAL, CORE, "Assertion Failure: %s, message: '%s', in file: %s, line: %d\n", expression, message, file, line );
}
