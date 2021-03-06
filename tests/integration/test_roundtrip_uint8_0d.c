/**
 * Checks that `idx_get_uint8` can be used to retrieve a value set using
 * `idx_set_uint8`.
 */
#include "idx.h"

#include "idx_test.h"


int main(void) {
    const size_t size = idx_size(IDX_TYPE_UINT8, 0);

    uint8_t *buffer = (uint8_t *) calloc(size, sizeof(uint8_t));
    idx_assert(buffer != NULL);

    idx_init(buffer, IDX_TYPE_UINT8, 0);

    for (int i = 0; i < 256; i++) {
        idx_set_uint8(buffer, i, 0);

        idx_assert(idx_validate(buffer, size) == IDX_NO_ERROR);
        idx_assert(idx_type(buffer) == IDX_TYPE_UINT8);
        idx_assert(idx_ndims(buffer) == 0);

        idx_assert(idx_get_uint8(buffer, 0) == i);
    }

    free(buffer);

    return 0;
}
