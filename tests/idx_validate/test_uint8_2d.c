#include "idx.h"

#include "idx_test.h"


int main(void) {
    IdxError err = idx_validate((
        "\x00\x00\x08\x02"
        "\x00\x00\x00\x03"
        "\x00\x00\x00\x03"
        "\x01\x00\x00"
        "\x00\x01\x00"
        "\x00\x00\x01"
    ), 21);

    idx_assert(!err);

    return 0;
}
