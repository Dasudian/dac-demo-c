/* clog: Extremely simple logger for C.
 *
 * Features:
 * - Implemented purely as a single header file.
 * - Create multiple loggers.
 * - Four log levels (debug, info, warn, error).
 * - Custom formats.
 * - Fast.
 *
 * Dependencies:
 * - Should conform to C89, C++98 (but requires vsnprintf, unfortunately).
 * - POSIX environment.
 *
 * USAGE:
 *
 * Include this header in any file that wishes to write to logger(s).  In
 * exactly one file (per executable), define CLOG_MAIN first (e.g. in your
 * main .c file).
 *
 *     #define CLOG_MAIN
 *     #include "clog.h"
 *
 * This will define the actual objects that all the other units will use.
 *
 * Loggers are identified by integers (0 - 15).  It's expected that you'll
 * create meaningful constants and then refer to the loggers as such.
 *
 * Example:
 *
 *  const int MY_LOGGER = 0;
 *
 *  int main() {
 *      int r;
 *      r = clog_init_path(MY_LOGGER, "my_log.txt");
 *      if (r != 0) {
 *          fprintf(stderr, "Logger initialization failed.\n");
 *          return 1;
 *      }
 *      clog_info(CLOG(MY_LOGGER), "Hello, world!");
 *      clog_free(MY_LOGGER);
 *      return 0;
 *  }
 *
 * The CLOG macro used in the call to clog_info is a helper that passes the
 * __FILE__ and __LINE__ parameters for you, so you don't have to type them
 * every time. (It could be prettier with variadic macros, but that requires
 * C99 or C++11 to be standards compliant.)
 *
 * Errors encountered by clog will be printed to stderr.  You can suppress
 * these by defining a macro called CLOG_SILENT before including clog.h.
 *
 * License: Do whatever you want. It would be nice if you contribute
 * improvements as pull requests here:
 *
 *   https://github.com/mmueller/clog
 *
 * Copyright 2013 Mike Mueller <mike@subfocal.net>.
 *
 * As is; no warranty is provided; use at your own risk.
 */
#ifndef DSD_LOG_H__
#define DSD_LOG_H__

#if defined __cplusplus
extern "C"
{
#endif


#define SDK_LOG 0
#define CLOG_MAIN

enum clog_level {
    CLOG_DEBUG,
    CLOG_INFO,
    CLOG_WARN,
    CLOG_ERROR
};


/* Number of loggers that can be defined. */
#define CLOG_MAX_LOGGERS 16

/* Format strings cannot be longer than this. */
#define CLOG_FORMAT_LENGTH 256

/* Formatted times and dates should be less than this length. If they are not,
 * they will not appear in the log. */
#define CLOG_DATETIME_LENGTH 256

/* Default format strings. */
#define CLOG_DEFAULT_FORMAT "%d %t %f(%n): %l: %m\n"
#define CLOG_DEFAULT_DATE_FORMAT "%Y-%m-%d"
#define CLOG_DEFAULT_TIME_FORMAT "%H:%M:%S"

int clog_init_path(int id, const char *const path);
int clog_init_fd(int id, int fd);
int clog_set_level(int id, enum clog_level level);

void clog_free(int id);
void clog_debug(const char *sfile, int sline, int id, const char *fmt, ...);
void clog_info(const char *sfile, int sline, int id, const char *fmt, ...);
void clog_warn(const char *sfile, int sline, int id, const char *fmt, ...);
void clog_error(const char *sfile, int sline, int id, const char *fmt, ...);

int dsd_log_init();

#define dsd_log_info(fmt, ...) do{clog_info(CLOG(SDK_LOG), fmt,##__VA_ARGS__);}while(0)
#define dsd_log_warn(fmt, ...) do{clog_warn(CLOG(SDK_LOG), fmt,##__VA_ARGS__);}while(0)
#define dsd_log_error(fmt, ...) do{clog_error(CLOG(SDK_LOG), fmt,##__VA_ARGS__);}while(0)
#define dsd_log_debug(fmt, ...) do{clog_debug(CLOG(SDK_LOG), fmt,##__VA_ARGS__);}while(0)
#define dsd_log_set_level(level) do{clog_set_level(SDK_LOG, level);}while(0)
#define CLOG(id) __FILE__, __LINE__, id

#if defined __cplusplus
}
#endif



#endif /* __CLOG_H__ */
