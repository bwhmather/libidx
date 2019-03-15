#include "idx.h"

#include "idx_test.h"

#include <limits.h>


int main(void) {
    for (IdxError err = INT_MIN; err < INT_MAX; err++) {
        if (
            (err == IDX_NO_ERROR) ||
            (err == IDX_ERROR_TRUNCATED) ||
            (err == IDX_ERROR_OVERALLOCATED) ||
            (err == IDX_ERROR_BAD_PADDING) ||
            (err == IDX_ERROR_UNKNOWN_TYPE_CODE) ||
            (err == IDX_ERROR_OVERFLOW)
        ) {
            continue;
        }
        idx_assert(!strcmp(
            idx_error_string(err),
            "unknown error"
        ));
    }
    return 0;
}

