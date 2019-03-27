/**
 * Checks that `idx_type` will correctly identify a structure containing a
 * single double.
 */
#include "idx.h"

#include "idx_test.h"


int main(void) {
    const uint8_t data[] = {
        0x00, 0x00, 0x0e, 0x00,
        0x40, 0x09, 0x21, 0xfb, 0x54, 0x44, 0x2d, 0x18,
    };
    idx_assert(idx_type(data) == IDX_TYPE_DOUBLE);

    return 0;
}
