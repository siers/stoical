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
    char timestr[255];

    if (msgloglvl >= loglvl)
        return;

    va_start(ap, fmt);

    /* Generate time string. */
    t = time(NULL);
    strftime(timestr, 255, timeformat, localtime(&t));

    /* Generate the whine and output it. */
    vasprintf(&str, fmt, ap);
    pthread_mutex_lock(&printf_lock);
    fprintf(msgloglvl == MSG_ERR ? stderr : stdout, "[%5i|%s] %s:%i %s\n",
            (int) getpid(), timestr,
            file, line,
            str);
    pthread_mutex_unlock(&printf_lock);

    free(str);
}
