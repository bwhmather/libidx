import ctypes
import os


_lib_path = os.path.join(
    os.path.abspath(os.path.dirname(__file__)),
    '..',
    'build',
    'libidx.so',
)
_lib = ctypes.cdll.LoadLibrary(_lib_path)


def idx_type(data):
    return _lib.idx_type(ctypes.c_char_p(data))


def idx_ndims(data):
    _lib.idx_ndims.restype = ctypes.c_uint8
    return _lib.idx_ndims(ctypes.c_char_p(data))


def idx_bound(data, dim):
    _lib.idx_ndims.restype = ctypes.c_uint8
    return _lib.idx_bound(ctypes.c_char_p(data), ctypes.c_uint8(dim))


def idx_size(type_code, *bounds):
    _lib.idx_size.restype = ctypes.c_size_t
    return _lib.idx_size(
        ctypes.c_int(type_code), ctypes.c_int(len(bounds)),
        *[ctypes.c_int32(bound) for bound in bounds],
    )


def idx_init(type_code, *bounds):
    _lib.idx_init.restype = None
    return _lib.idx_init(
        ctypes.c_int(type_code), ctypes.c_int(len(bounds)),
        *[ctypes.c_int32(bound) for bound in bounds],
    )


def idx_validate(data, size):
    return _lib.idx_validate(ctypes.c_char_p(data), ctypes.c_uint8(size))
