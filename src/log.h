#pragma once

#include <stdlib.h>

enum {
    MSG_NORM,       /* Normal */
    MSG_ADD,        /* Additional */
    MSG_DEBUG,      /* Debug */
    MSG_ERR = -1    /* Error -- is always printed and goes to stderr */
};

#define log(fmt, ...) \
    log_whine(MSG_NORM, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

#define log_a(fmt, ...) \
    log_whine(MSG_ADD, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

#define log_d(fmt, ...) \
    log_whine(MSG_DEBUG, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

#define log_e(fmt, ...) \
    log_whine(MSG_ERR, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

#define assert(condition, fmt, ...) \
    if (!(condition)) \
        log_whine(MSG_ERR, __FILE__, __LINE__, fmt, ##__VA_ARGS__); \

#define assert_fatal(condition, fmt, ...) \
    if (!(condition)) { \
        log_whine(MSG_ERR, __FILE__, __LINE__, fmt, ##__VA_ARGS__); \
        exit(EXIT_FAILURE); \
    }

void log_whine(int msgloglvl, char* file, int line, const char *fmt, ...);
