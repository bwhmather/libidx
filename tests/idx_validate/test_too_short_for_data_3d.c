/**
 * Checks that `idx_validate` will correctly reject structures that have not
 * been allocated enough space for all of their data.
 */
#include "idx.h"

#include "idx_test.h"


int main(void) {
    // Data is one byte shorter than declared in the header..
    const uint8_t data[] = {
        0x00, 0x00, 0x0b, 0x03,
        0x00, 0x00, 0x00, 0x02,
        0x00, 0x00, 0x00, 0x02,
        0x00, 0x00, 0x00, 0x02,
        0x01, 0x02, 0x03, 0x04,
        0x05, 0x06, 0x07, 0x08,
        0x09, 0x0a, 0x0b, 0x0c,
        0x0e, 0x0f, 0xa0,
    };

    idx_assert(idx_validate(data, 31) == IDX_ERROR_TRUNCATED);

    return 0;
}
