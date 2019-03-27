/**
 * Checks that `idx_type` will correctly identify a structure containing 32 bit
 * integers.
 */
#include "idx.h"

#include "idx_test.h"


int main(void) {
    const uint8_t data[] = {
        0x00, 0x00, 0x0c, 0x00,
        0xaa, 0xbb, 0xcc, 0xdd,
    };
    idx_assert(idx_type(data) == IDX_TYPE_INT32);

    return 0;
}
