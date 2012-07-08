#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include "log.h"

extern int loglvl;
char timeformat[] = "%H%M.%S";
pthread_mutex_t printf_lock = PTHREAD_MUTEX_INITIALIZER;

void
log_whine(int msgloglvl, char* file, int line, const char *fmt, ...)
{
    va_list ap;
    char* str;
    long int t;
    struct tm* tmp;
    char timestr[255];

    if (msgloglvl >= loglvl)
        return;

    va_start(ap, fmt);

    /* Generate time string. */
    t = time(NULL);
    tmp = localtime(&t);
    strftime(timestr, 255, timeformat, tmp);

    /* Generate the whine and output it. */
    vasprintf(&str, fmt, ap);
    pthread_mutex_lock(&printf_lock);
    if (msgloglvl == MSG_ERR)
        t = (long int) stderr;
    else
        t = (long int) stdout;
    fprintf((FILE*) t, "[%5i|%s] %s:%i %s\n",
            (int) getpid(), timestr,
            file, line,
            str);
    pthread_mutex_unlock(&printf_lock);

    free(str);
}
