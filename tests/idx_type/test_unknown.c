/**
 * Checks that `idx_type` will correctly identify a structure containing 16 bit
 * integers..
 */
#include "idx.h"

#include "idx_test.h"


int main(void) {
    idx_assert_aborts(idx_type("\x00\x00\x0A\x00\xFE"));

    return 0;
}
