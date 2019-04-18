/**
 * Tests that `idx_get_double` can read positive zero.
 */
#include "idx.h"

#include "idx_test.h"


int main(void) {
    const uint8_t data[] = {
        0x00, 0x00, 0x0e, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    };

    const double expected = 0.0;
    idx_assert(idx_get_double(data, 0) == expected);

    return 0;
}

