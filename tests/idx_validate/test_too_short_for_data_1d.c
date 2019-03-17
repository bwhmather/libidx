#include "idx.h"

#include "idx_test.h"


int main(void) {
    IdxError err = idx_validate((
        "\x00\x00\x08\x01"
        "\x00\x00\x00\x03"
        "\x01\x02\x03"
    ), 9);
    idx_assert(err == IDX_ERROR_TRUNCATED);

    return 0;
}
