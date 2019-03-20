/**
 * Checks that `idx_validate` correctly flags bad padding.
 */
#include "idx.h"

#include "idx_test.h"


int main(void) {
    uint8_t data[] = {
        0x00, 0x00, 0x08, 0x01,
        0x00, 0x00, 0x00, 0x04,
        0x01, 0x02, 0x03, 0x04,
    };

    for (uint16_t padding = 0xffff; padding > 0; padding--) {
        data[0] = (uint8_t) ((padding >> 8) & 0xff);
        data[1] = (uint8_t) ((padding >> 0) & 0xff);

        idx_assert(idx_validate(data, 12) == IDX_ERROR_BAD_PADDING);
    }

    return 0;
}
