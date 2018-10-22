import unittest
from . import test_bound
from . import test_error_string
from . import test_size
from . import test_type
from . import test_validate


loader = unittest.TestLoader()
suite = unittest.TestSuite((
    loader.loadTestsFromModule(test_bound),
    loader.loadTestsFromModule(test_error_string),
    loader.loadTestsFromModule(test_size),
    loader.loadTestsFromModule(test_type),
    loader.loadTestsFromModule(test_validate),
))
