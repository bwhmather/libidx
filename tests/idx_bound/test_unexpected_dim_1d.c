#include "idx.h"

#include "idx_test.h"


int main(void) {
    const uint8_t data[] = {
        0x00, 0x00, 0x08, 0x00, 0xab,
    };

    idx_assert_aborts(idx_bound(data, 1));

    return 0;
}
