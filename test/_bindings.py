import ctypes
import os


_lib_path = os.path.join(
    os.path.abspath(os.path.dirname(__file__)),
    '..',
    'build',
    'libidx.so',
)
_lib = ctypes.cdll.LoadLibrary(_lib_path)


def _uint8_t(value):
    result = ctypes.c_uint8(value)
    if result.value != value:
        raise ValueError(value)
    return result


def _int8_t(value):
    result = ctypes.c_int8(value)
    if result.value != value:
        raise ValueError(value)
    return result


def _uint16_t(value):
    result = ctypes.c_uint16(value)
    if result.value != value:
        raise ValueError(value)
    return result


def _int16_t(value):
    result = ctypes.c_int16(value)
    if result.value != value:
        raise ValueError(value)
    return result


def _uint32_t(value):
    result = ctypes.c_uint32(value)
    if result.value != value:
        raise ValueError(value)
    return result


def _int32_t(value):
    if -2**32 >= value >= 2**32:
        raise ValueError(value)
    return ctypes.c_int(value)


def _float_t(value):
    return ctypes.c_float(value)


def _double_t(value):
    return ctypes.c_double(value)


def _size_t(value):
    result = ctypes.c_size_t(value)
    if result.value != value:
        raise ValueError(value)
    return result


def idx_type(data):
    return _lib.idx_type(ctypes.c_char_p(data))


def idx_ndims(data):
    _lib.idx_ndims.restype = ctypes.c_uint8
    return _lib.idx_ndims(ctypes.c_char_p(data))


def idx_bound(data, dim):
    _lib.idx_ndims.restype = ctypes.c_uint8
    return _lib.idx_bound(ctypes.c_char_p(data), _uint8_t(dim))


def idx_size(type_code, *bounds):
    _lib.idx_size.restype = ctypes.c_size_t
    return _lib.idx_size(
        _int32_t(type_code), _int32_t(len(bounds)),
        *[_uint32_t(bound) for bound in bounds],
    )


def idx_init(type_code, *bounds):
    _lib.idx_init.restype = None
    return _lib.idx_init(
        _int32_t(type_code), _int32_t(len(bounds)),
        *[_uint32_t(bound) for bound in bounds],
    )


def idx_validate(data, size):
    return _lib.idx_validate(ctypes.c_char_p(data), _size_t(size))
