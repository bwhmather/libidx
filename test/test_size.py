import unittest
from ._bindings import idx_size


class IdxSizeTestCase(unittest.TestCase):
    def test_size_uint8_1d(self):
        self.assertEqual(idx_size(0x08, 0), 5)

    def test_size_int8_1d(self):
        self.assertEqual(idx_size(0x09, 0), 5)

    def test_size_int16_1d(self):
        self.assertEqual(idx_size(0x0B, 0), 6)

    def test_size_int32_1d(self):
        self.assertEqual(idx_size(0x0C, 0), 8)

    def test_size_float_1d(self):
        self.assertEqual(idx_size(0x0D, 0), 8)

    def test_size_double_1d(self):
        self.assertEqual(idx_size(0x0E, 0), 12)
