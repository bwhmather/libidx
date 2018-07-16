import ctypes
import multiprocessing
import os
import unittest


_lib_path = os.path.join(
    os.path.abspath(os.path.dirname(__file__)),
    'build',
    'libidx.so',
)
_lib = ctypes.cdll.LoadLibrary(_lib_path)


class AbnormalExitError(Exception):
    pass


def _call_worker(fn, pipe, *args, **kwargs):
    result = fn(*args, **kwargs)
    pipe.send(result)
    pipe.close()


def call_in_proc(fn, *args, **kwargs):
    rpipe, wpipe = multiprocessing.Pipe(duplex=False)
    proc = multiprocessing.Process(
        target=_call_worker, daemon=True,
        args=[fn, wpipe] + list(args), kwargs=kwargs,
    )
    proc.start()
    proc.join()
    if proc.exitcode != 0:
        raise AbnormalExitError(proc.exitcode)
    return proc.recv()


def idx_type(data):
    return _lib.idx_type(ctypes.c_char_p(data))


def idx_ndims(data):
    _lib.idx_ndims.restype = ctypes.c_uint8
    return _lib.idx_ndims(ctypes.c_char_p(data))


def idx_bound(data, dim):
    _lib.idx_ndims.restype = ctypes.c_uint8
    return _lib.idx_bound(ctypes.c_char_p(data), ctypes.c_uint8(dim))


def idx_size(type_code, dimensions):
    _lib.idx_size.restype = ctypes.c_size_t
    return _lib.idx_size(ctypes.c_int(type_code), ctypes.c_uint8(dimensions))


def idx_init(type_code, dimensions):
    _lib.idx_init.restype = None
    return _lib.idx_init(ctypes.c_int(type_code), ctypes.c_uint8(dimensions))


def idx_validate(data, size):
    return _lib.idx_validate(ctypes.c_char_p(data), ctypes.c_uint8(size))


class IdxTypeTestCase(unittest.TestCase):
    def test_uint8(self):
        type_code = idx_type(b'\x00\x00\x08\x00\xFE')
        self.assertEqual(type_code, 0x08)


class IdxBoundTestCase(unittest.TestCase):
    def test_unexpected_dim_1d(self):
        with self.assertRaises(AbnormalExitError):
            call_in_proc(idx_bound, b'\x00\x00\x08\x00\xAB', 1)


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


if __name__ == '__main__':
    unittest.main()
