/**
 * Checks that `idx_type` will correctly identify a structure containing 16 bit
 * integers.
 */
#include "idx.h"

#include "idx_test.h"


int main(void) {
    const uint8_t data[] = {
        0x00, 0x00, 0x0b, 0x00,
        0x01, 0x02,
    };
    idx_assert(idx_type(data) == IDX_TYPE_INT16);

    return 0;
}
