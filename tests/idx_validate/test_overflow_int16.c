/**
 * Checks that `idx_validate` will safely reject arrays that are longer than
 * a `size_t`.
 */
#include "idx.h"

#include "idx_test.h"


int main(void) {
    // Note that we can't actually allocate an array longer than the maximum
    // allowed by a 64 bit `size_t`.  This doesn't matter as the overflow will
    // happen before we hit the comparison.
    // Bounds chosen to multiply to exactly two to the power of 64 minus 16,
    // over 2 meaning that the structure is one byte two big.
    const uint8_t data[] = {
        0x00, 0x00, 0x0B, 0x03,
        0x00, 0x00, 0x05, 0x29,
        0x03, 0x54, 0x4a, 0xb8,
        0x07, 0x73, 0x62, 0xf1,
    };

    idx_assert(idx_validate(data, 16) == IDX_ERROR_OVERFLOW);

    return 0;
}
