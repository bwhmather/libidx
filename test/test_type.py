import unittest
from ._bindings import idx_type


class IdxTypeTestCase(unittest.TestCase):
    def test_uint8(self):
        type_code = idx_type(b'\x00\x00\x08\x00\xFE')
        self.assertEqual(type_code, 0x08)
