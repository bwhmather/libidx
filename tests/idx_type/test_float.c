/**
 * Checks that `idx_type` will correctly identify a structure containing a
 * single float.
 */
#include "idx.h"

#include "idx_test.h"


int main(void) {
    const uint8_t data[] = {
        0x00, 0x00, 0x0d, 0x00,
        0x40, 0x49, 0x0f, 0xdb,
    };
    idx_assert(idx_type(data) == IDX_TYPE_FLOAT);

    return 0;
}
