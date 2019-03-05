#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>


#define idx_assert(idx_test_condition) do {                                 \
    if (!(idx_test_condition)) {                                            \
        fprintf(                                                            \
            stderr, "%s:%i %s: Assertion `%s' failed",                      \
            __FILE__, __LINE__, __func__, #idx_test_condition               \
        );                                                                  \
        abort();                                                            \
    }                                                                       \
} while (0)

static inline void idx_test_internal_on_sigabrt(int signal) {
    exit(0);
}

#define idx_assert_aborts(idx_test_expression) do {                         \
    struct sigaction idx_test_handler_old;                                  \
    struct sigaction idx_test_handler_new;                                  \
    memset(&idx_test_handler_new, 0, sizeof(idx_test_handler_new));         \
    sigemptyset(&idx_test_handler_new.sa_mask);                             \
    idx_test_handler_new.sa_handler = &idx_test_internal_on_sigabrt;        \
    sigaction(SIGABRT, &idx_test_handler_new, &idx_test_handler_old);       \
    idx_test_expression;                                                    \
    sigaction(SIGABRT, &idx_test_handler_old, NULL);                        \
    fprintf(                                                                \
        stderr, "%s:%i %s: Expression `%s' did not abort",                  \
        __FILE__, __LINE__, __func__, #idx_test_expression                  \
    );                                                                      \
    abort();                                                                \
} while(0)
