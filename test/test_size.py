import unittest
from ._bindings import idx_size


class IdxSizeTestCase(unittest.TestCase):
    def test_size_uint8_0d(self):
        self.assertEqual(idx_size(0x08), 5)

    def test_size_int8_0d(self):
        self.assertEqual(idx_size(0x09), 5)

    def test_size_int16_0d(self):
        self.assertEqual(idx_size(0x0B), 6)

    def test_size_int32_0d(self):
        self.assertEqual(idx_size(0x0C), 8)

    def test_size_float_0d(self):
        self.assertEqual(idx_size(0x0D), 8)

    def test_size_double_0d(self):
        self.assertEqual(idx_size(0x0E), 12)

    def test_size_max_uint8(self):
        # Tests that correct size is given for a structure that hits the limit
        # of what can fit in a `size_t`.
        # Assumes that `size_t` is 64 bits.
        # Constants derived from the prime factors of 2^64 - 25.  -25 is enough
        # for 1 byte to stay in bounds plus 5 * 4 bytes to store the bounds
        # plus 4 bytes for the magic number.
        size = idx_size(0x08, 4294967291, 3384529, 47, 9, 3)
        self.assertEqual(size, 2**64 - 1)

    def test_size_overflow_header_uint8(self):
        # Tests that a structure where the space to fit the values fits in a
        # `size_t`, but the total space does not does not overflow.
        # Assumes that `size_t` is 64 bits.
        # Constants are the prime factors of 2^64 - 26.  With a header for 6
        # dimensions, this is 22 bytes to large to be described by a `size_t`.
        size = idx_size(0x08, 2, 5, 191, 421, 90679, 252986611)
        self.assertEqual(size, 0)

    def test_size_overflow_bounds_uint8(self):
        # Checks that the overflow checks work when multiplying bounds.
        size = idx_size(0x08, 2**32 - 1, 2**32 - 1, 2)
        self.assertEqual(size, 0)
