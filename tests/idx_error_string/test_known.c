/**
 * Checks that `idx_error_string` returns expected value for know error types.
 */
#include "idx.h"

#include "idx_test.h"

#include <string.h>


int main(void) {
    idx_assert(!strcmp(
        idx_error_string(IDX_NO_ERROR),
        "no error"
    ));
    idx_assert(!strcmp(
        idx_error_string(IDX_ERROR_TRUNCATED),
        "truncated"
    ));
    idx_assert(!strcmp(
        idx_error_string(IDX_ERROR_OVERALLOCATED),
        "overallocated"
    ));
    idx_assert(!strcmp(
        idx_error_string(IDX_ERROR_BAD_PADDING),
        "bad padding"
    ));
    idx_assert(!strcmp(
        idx_error_string(IDX_ERROR_UNKNOWN_TYPE_CODE),
        "unknown type code"
    ));
    idx_assert(!strcmp(
        idx_error_string(IDX_ERROR_OVERFLOW),
        "overflow"
    ));

    return 0;
}
