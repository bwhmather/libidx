import unittest
from ._bindings import idx_validate


class IdxValidateTestCase(unittest.TestCase):
    def test_too_short_for_header(self):
        err = idx_validate(b'\x00\x00\x08\x00\xFE', 3)
        self.assertNotEqual(err, 0)

    def test_too_short_for_bounds(self):
        err = idx_validate((
            b'\x00\x00\x08\x02'
            b'\x00\x00\x00\x03'
            b'\x00\x00\x00\x03'
            b'\x01\x00\x00'
            b'\x00\x01\x00'
            b'\x00\x00\x01'
        ), 5)
        self.assertNotEqual(err, 0)

    def test_too_short_for_data_1d(self):
        pass

    def test_too_short_for_data_3d(self):
        pass
