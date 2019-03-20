/**
 * Checks that `idx_validate` correctly flags bad padding.
 */
#include "idx.h"

#include "idx_test.h"


int main(void) {
    uint8_t data[] = {
        0xde, 0xad, 0x08, 0x01,
        0x00, 0x00, 0x00, 0x04,
        0x01, 0x02, 0x03, 0x04,
    };

    idx_assert(idx_validate(data, 12) == IDX_ERROR_BAD_PADDING);

    return 0;
}
