/**
 * Checks that `idx_validate` will accept a valid zero-dimensional uint8 array.
 */
#include "idx.h"

#include "idx_test.h"


int main(void) {
    const uint8_t data[] = {
        0x00, 0x00, 0x08, 0x00,
        0xfe,
    };

    idx_assert(!idx_validate(data, 5));

    return 0;
}
