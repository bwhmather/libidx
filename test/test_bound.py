import unittest
from ._bindings import idx_bound
from ._helpers import call_in_proc, AbnormalExitError


class IdxBoundTestCase(unittest.TestCase):
    def test_unexpected_dim_1d(self):
        with self.assertRaises(AbnormalExitError):
            call_in_proc(idx_bound, b'\x00\x00\x08\x00\xAB', 1)
