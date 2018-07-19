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
