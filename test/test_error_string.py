import unittest
import re
import random

from ._bindings import idx_error_string


class IdxErrorStringTestCase(unittest.TestCase):

    def test_known(self):
        for error_code, expected in [
            (0, b"no error"),
            (1, b"truncated"),
            (2, b"overallocated"),
            (3, b"bad padding"),
            (4, b"unknown type code"),
            (5, b"overflow"),
        ]:
            error_string = idx_error_string(error_code)
            self.assertEqual(error_string, expected)

    def test_random(self):
        pattern = re.compile(rb'^[a-z][a-z -]{0,76}[a-z]$')
        for _ in range(10000):
            error_code = random.randint(-2**31, 2**31)
            error_string = idx_error_string(error_code)
            self.assertRegex(error_string, pattern)

