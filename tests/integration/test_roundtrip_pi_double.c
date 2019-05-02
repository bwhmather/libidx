/**
 * Checks that libidx can be used to save pi to a zero dimensional double array
 * and then read it back out.
 */
#include "idx.h"

#include "idx_test.h"

#include <math.h>


int main(void) {
    const double pi = M_PI;

    const size_t size = idx_size(IDX_TYPE_DOUBLE, 0);

    uint8_t *buffer = (uint8_t *) calloc(size, sizeof(uint8_t));
    idx_assert(buffer != NULL);

    idx_init(buffer, IDX_TYPE_DOUBLE, 0);
    idx_set_double(buffer, pi, 0);

    idx_assert(idx_validate(buffer, size) == IDX_NO_ERROR);
    idx_assert(idx_type(buffer) == IDX_TYPE_DOUBLE);
    idx_assert(idx_ndims(buffer) == 0);

    idx_assert(idx_get_double(buffer, 0) == pi);

    free(buffer);

    return 0;
}
