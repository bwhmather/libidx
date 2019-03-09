#include "idx.h"

#include "idx_test.h"

#include <limits.h>


int main(int argc, char **argv) {
    for (IdxError err = INT_MIN; err < INT_MAX; err++) {
        if (err >= 0 && err <= 5) {
            continue;
        }
        idx_assert(!strcmp(
            idx_error_string(err),
            "unknown error"
        ));
    }
    return 0;
}

