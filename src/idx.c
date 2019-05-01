/**
 * Copyright 2018 Ben Mather <bwhmather@bwhmather.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
*/

#include "idx.h"

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#define IDX_CONCAT_INNER(A, B) A ## B
#define IDX_CONCAT(A, B) IDX_CONCAT_INNER(A, B)

#define IDX_TYPE(TYPE) IDX_TYPE_ ## TYPE

#define IDX_CTYPE_UINT8 uint8_t
#define IDX_CTYPE_INT8 int8_t
#define IDX_CTYPE_INT16 int16_t
#define IDX_CTYPE_INT32 int32_t
#define IDX_CTYPE_FLOAT float
#define IDX_CTYPE_DOUBLE double
#define IDX_CTYPE(TYPE) IDX_CTYPE_ ## TYPE

#define IDX_FNAME_UINT8 uint8
#define IDX_FNAME_INT8 int8
#define IDX_FNAME_INT16 int16
#define IDX_FNAME_INT32 int32
#define IDX_FNAME_FLOAT float
#define IDX_FNAME_DOUBLE double
#define IDX_FNAME(TYPE) IDX_FNAME_ ## TYPE

#define IDX_SIZE_UINT8 1
#define IDX_SIZE_INT8 1
#define IDX_SIZE_INT16 2
#define IDX_SIZE_INT32 4
#define IDX_SIZE_FLOAT 4
#define IDX_SIZE_DOUBLE 8
#define IDX_SIZE(TYPE) IDX_SIZE_ ## TYPE


static size_t idx_type_size(IdxType type) {
    switch (type) {
    case IDX_TYPE_UINT8:
        return IDX_SIZE_UINT8;
    case IDX_TYPE_INT8:
        return IDX_SIZE_INT8;
    case IDX_TYPE_INT16:
        return IDX_SIZE_INT16;
    case IDX_TYPE_INT32:
        return IDX_SIZE_INT32;
    case IDX_TYPE_FLOAT:
        return IDX_SIZE_FLOAT;
    case IDX_TYPE_DOUBLE:
        return IDX_SIZE_DOUBLE;
    default:
        assert(false);
    }
}

bool idx_type_supported(IdxType type) {
    switch (type) {
    case IDX_TYPE_UINT8:
    case IDX_TYPE_INT8:
    case IDX_TYPE_INT16:
    case IDX_TYPE_INT32:
    case IDX_TYPE_FLOAT:
    case IDX_TYPE_DOUBLE:
        return true;
    default:
        return false;
    }
}

static inline uint8_t idx_read_uint8(const uint8_t bytes[1]) {
    return (uint8_t) bytes[0];
}

static inline int8_t idx_read_int8(const uint8_t bytes[1]) {
    return (int8_t) bytes[0];
}

static inline uint16_t idx_read_uint16(const uint8_t bytes[2]) {
    return (
        ((uint16_t) bytes[0] << 8) |
        ((uint16_t) bytes[1] << 0)
    );
}

static inline int16_t idx_read_int16(const uint8_t bytes[4]) {
    return (int16_t) idx_read_uint16(bytes);
}

static inline uint32_t idx_read_uint32(const uint8_t bytes[4]) {
    return (
        ((uint32_t) bytes[0] << 24) |
        ((uint32_t) bytes[1] << 16) |
        ((uint32_t) bytes[2] << 8) |
        ((uint32_t) bytes[3] << 0)
    );
}

static inline int32_t idx_read_int32(const uint8_t bytes[4]) {
    return (int32_t) idx_read_uint32(bytes);
}

static inline float idx_read_float(const uint8_t bytes[4]) {
    return (float) idx_read_uint32(bytes);
}

static inline double idx_read_double(const uint8_t bytes[8]) {
    bool negative = (bytes[0] & 0x80) == 0x80;

    uint_fast16_t biased_exponent = (uint_fast16_t) (
        ((uint_fast16_t) (bytes[0] & 0x7f) << 4) |
        ((uint_fast16_t) (bytes[1] & 0xf0) >> 4)
    );

    uint_fast64_t biased_significand = (uint_fast64_t) (
        ((uint_fast64_t) (bytes[1] & 0x0f) << 48) |
        ((uint_fast64_t) bytes[2] << 40) |
        ((uint_fast64_t) bytes[3] << 32) |
        ((uint_fast64_t) bytes[4] << 24) |
        ((uint_fast64_t) bytes[5] << 16) |
        ((uint_fast64_t) bytes[6] << 8) |
        ((uint_fast64_t) bytes[7] << 0)
    );

    double value;

    if (biased_exponent == 0x7ff) {
        if (biased_significand == 0) {
            value = INFINITY;
        } else {
            value = NAN;
        }
    } else if (biased_exponent == 0) {
        const int exponent = -1021;
        const double significand = ldexp((double) biased_significand, -53);
        value = ldexp(significand, - 1021);
    } else {
        biased_significand |= 0x10000000000000;
        const int exponent = ((int) biased_exponent) - 1022;
        const double significand = ldexp((double) biased_significand, -53);
        value = ldexp(significand, exponent);
    }

    value = copysign(value, negative ? -1.0 : 1.0);

    return value;
}

static inline void idx_write_uint8(uint8_t value, uint8_t bytes[1]) {
    bytes[0] = value;
}

static inline void idx_write_int8(int8_t value, uint8_t bytes[1]) {
    uint8_t twos_complement;

    if (value < 0) {
        twos_complement = (0xff - (uint8_t) abs((int) value)) + 1;
    } else {
        twos_complement = (uint8_t) value;
    }

    idx_write_uint8(twos_complement, bytes);
}

static inline void idx_write_uint16(uint16_t value, uint8_t bytes[2]) {
    bytes[0] = (value >> 8) & 0xff;
    bytes[1] = (value >> 0) & 0xff;
}

static inline void idx_write_int16(int16_t value, uint8_t bytes[2]) {
    uint16_t twos_complement;

    if (value < 0) {
        twos_complement = (0xffff - (uint16_t) abs((int) value)) + 1;
    } else {
        twos_complement = (uint16_t) value;
    }

    idx_write_uint16((uint16_t) twos_complement, bytes);
}

static inline void idx_write_uint32(uint32_t value, uint8_t bytes[4]) {
    bytes[0] = (value >> 24) & 0xff;
    bytes[1] = (value >> 16) & 0xff;
    bytes[2] = (value >> 8) & 0xff;
    bytes[3] = (value >> 0) & 0xff;
}

static inline void idx_write_int32(int32_t value, uint8_t bytes[4]) {
    idx_write_uint32((uint32_t) value, bytes);
}

static inline void idx_write_float(float value, uint8_t bytes[4]) {
    uint_fast32_t biased_significand;
    uint_fast8_t biased_exponent;

    bool negative = signbit(value) ? true : false;

    if (isnan(value)) {
        // TODO distinguish between quiet and signalling NaNs.
        biased_exponent = 0xff;
        biased_significand = 0x01;

    } else if (isinf(value)) {
        biased_exponent = 0xff;
        biased_significand = 0x00;

    } else {
        int exponent = 0;
        float significand = frexp(fabs(value), &exponent);

        if (exponent < -125) {
            // Value is sub-normal.
            biased_significand = (uint_fast64_t) truncf(ldexpf(
                significand, 24 + (exponent + 125)
            ));
            biased_exponent = 0;
        } else {
            // Value is normalized.
            biased_significand = (uint_fast32_t) truncf(ldexpf(
                significand, 24
            ));
            biased_exponent = (uint_fast8_t) (exponent + 126);
        }

        if (biased_significand == 0) {
            biased_exponent = 0;
        }
    }

    // Write sign bit.
    bytes[0] = negative ? 0x80 : 0x00;

    // Write exponent.
    bytes[0] |= (biased_exponent >> 1) & 0x7f;
    bytes[1] = (biased_exponent << 7) & 0x80;

    // Write significand.
    bytes[1] |= (biased_significand >> 16) & 0x7f;
    bytes[2] = (biased_significand >> 8) & 0xff;
    bytes[3] = (biased_significand >> 0) & 0xff;

}

static inline void idx_write_double(double value, uint8_t bytes[8]) {
    // From RFC-1014 (https://tools.ietf.org/html/rfc1014):
    //     +------+------+------+------+------+------+------+------+
    //     |byte 0|byte 1|byte 2|byte 3|byte 4|byte 5|byte 6|byte 7|
    //     S|    E   |                    F                        |
    //     +------+------+------+------+------+------+------+------+
    //     1|<--11-->|<-----------------52 bits------------------->|
    //     <-----------------------64 bits------------------------->
    uint_fast64_t biased_significand;
    uint_fast16_t biased_exponent;

    bool negative = signbit(value) ? true : false;

    if (isnan(value)) {
        // TODO distinguish between quiet and signalling NaNs.
        biased_exponent = 0x7ff;
        biased_significand = 0x01;

    } else if (isinf(value)) {
        biased_exponent = 0x7ff;
        biased_significand = 0x00;

    } else {
        int exponent = 0;
        double significand = frexp(fabs(value), &exponent);

        if (exponent < -1021) {
            // Value is sub-normal.
            biased_significand = (uint_fast64_t) trunc(ldexp(
                significand, 53 + (exponent + 1021)
            ));
            biased_exponent = 0;
        } else {
            // Value is normalized.
            biased_significand = (uint_fast64_t) trunc(ldexp(significand, 53));
            biased_exponent = (uint_fast16_t) (exponent + 1022);
        }

        if (biased_significand == 0) {
            biased_exponent = 0;
        }
    }

    // Write sign bit.
    bytes[0] = negative ? 0x80 : 0x00;

    // Write exponent.
    bytes[0] |= (biased_exponent >> 4) & 0x7f;
    bytes[1] = (biased_exponent << 4) & 0xf0;

    // Write significand.
    bytes[1] |= (biased_significand >> 48) & 0x0f;
    bytes[2] = (biased_significand >> 40) & 0xff;
    bytes[3] = (biased_significand >> 32) & 0xff;
    bytes[4] = (biased_significand >> 24) & 0xff;
    bytes[5] = (biased_significand >> 16) & 0xff;
    bytes[6] = (biased_significand >> 8) & 0xff;
    bytes[7] = (biased_significand >> 0) & 0xff;
}

IdxType idx_type(const void *data) {
    const uint8_t *bytes = (const uint8_t *) data;
    return (IdxType) bytes[2];
}

uint8_t idx_ndims(const void *data) {
    const uint8_t *bytes = (const uint8_t *) data;
    return bytes[3];
}

size_t idx_bound(const void *data, uint8_t dim) {
    assert(dim < idx_ndims(data));
    const uint8_t *bytes = (const uint8_t *) data;
    return (size_t) idx_read_uint32(&bytes[4 + 4 * dim]);
}

size_t idx_size(IdxType type, int ndims, ...) {
    // Check that ndims can safely be stored as a uint8.
    if (ndims < 0 || ndims > 255) {
        return 0;
    }

    // Space required to store the size of each dimension.  `ndims` is limited
    // to 255, so this can't overflow.
    size_t header_size = 4 + (4 * ndims);

    if (!idx_type_supported(type)) {
        return 0;
    }
    size_t data_size = idx_type_size(type);

    va_list bounds;
    va_start(bounds, ndims);
    for (int dim = 0; dim < ndims; dim++) {
        uint32_t bound = va_arg(bounds, uint32_t);
        if (bound > (SIZE_MAX - header_size) / data_size) {
            return 0;
        }
        data_size *= bound;
    }

    return header_size + data_size;
}

void idx_init(void *data, IdxType type, int ndims, ...) {
    uint8_t *bytes = (uint8_t *) data;
    assert(ndims >= 0 && ndims <= 255);

    size_t header_size = 4 + (4 * ndims);

    size_t data_size = idx_type_size(type);

    idx_write_uint16(0, &bytes[0]);
    idx_write_uint8(type, &bytes[2]);
    idx_write_uint8(ndims, &bytes[3]);

    va_list bounds;
    va_start(bounds, ndims);

    for (int dim = 0; dim < ndims; dim++) {
        uint32_t bound = va_arg(bounds, uint32_t);
        assert(bound <= (SIZE_MAX - header_size) / data_size);
        idx_write_uint32(bound, &bytes[4 + 4 * dim]);
    }
}

IdxError idx_validate(const void *data, size_t size) {
    const uint8_t *bytes = (const uint8_t *) data;

    // Check that length is long enough to contain magic number.
    if (size < 4) {
        return IDX_ERROR_TRUNCATED;
    }

    // Parse the header.
    uint16_t magic = idx_read_uint16(&bytes[0]);
    IdxType type = (IdxType) idx_read_uint8(&bytes[2]);
    uint8_t ndims = idx_read_uint8(&bytes[3]);

    // Check that the first two bytes are zero.
    if (magic != 0) {
        return IDX_ERROR_BAD_PADDING;
    }

    size_t header_size = 4 + (size_t) ndims * 4;

    // Check that there is at least enough space to store the dimensions.
    // No risk of overflow because `ndims` is limited to 255.
    if (size < header_size) {
        return IDX_ERROR_TRUNCATED;
    }

    // Check type code is supported.  We can't validate the size of structures
    // containing data of a type that we do not recognize.
    if (!idx_type_supported(type)) {
        return IDX_ERROR_UNKNOWN_TYPE_CODE;
    }
    size_t data_size = idx_type_size(type);

    // Check length.
    for (int dim = 0; dim < ndims; dim++) {
        uint32_t bound = idx_read_uint32(&bytes[4 + (4 * dim)]);
        if (bound > (SIZE_MAX - header_size) / data_size) {
            return IDX_ERROR_OVERFLOW;
        }
        data_size *= bound;
    }

    size_t actual_size = data_size + header_size;

    // No risk of underflow as we have already checked that size is greater
    // than or equal to the size of the header.
    if (actual_size > size) {
        return IDX_ERROR_TRUNCATED;
    }

    if (actual_size < size) {
        return IDX_ERROR_OVERALLOCATED;
    }

    return IDX_NO_ERROR;
}

const char *idx_error_string(IdxError error) {
    switch (error) {
    case IDX_NO_ERROR:
        return "no error";
    case IDX_ERROR_TRUNCATED:
        return "truncated";
    case IDX_ERROR_OVERALLOCATED:
        return "overallocated";
    case IDX_ERROR_OVERFLOW:
        return "overflow";
    case IDX_ERROR_BAD_PADDING:
        return "bad padding";
    case IDX_ERROR_UNKNOWN_TYPE_CODE:
        return "unknown type code";
    default:
        return "unknown error";
    }
}

static size_t idx_data_offset_va(
    const void *data, int ndims, va_list indexes
) {
    // Check that number of dimensions match.
    assert(idx_ndims(data) == ndims);

    // Check bounds and figure out offset.
    size_t offset = 0;
    for (int dim = 0; dim < ndims; dim++) {
        size_t index = va_arg(indexes, size_t);
        size_t stride = idx_bound(data, dim);

        assert(index < stride);

        offset *= stride;
        offset += index;
    }

    va_end(indexes);

    return offset;
}

#define IDX_GET_FN(TYPE)                                                      \
IDX_CTYPE(TYPE) IDX_CONCAT(idx_get_, IDX_FNAME(TYPE))(                        \
    const void *data, int ndims, ...                                          \
) {                                                                           \
    va_list indexes;                                                          \
    va_start(indexes, ndims);                                                 \
                                                                              \
    assert(idx_type(data) == IDX_TYPE(TYPE));                                 \
                                                                              \
    size_t offset = idx_data_offset_va(                                       \
        data, ndims, indexes                                                  \
    );                                                                        \
                                                                              \
    const uint8_t *bytes = (const uint8_t *) data;                            \
    const uint8_t *element = &bytes[                                          \
        4 + 4 * ndims +                                                       \
        offset * IDX_SIZE(TYPE)                                               \
    ];                                                                        \
                                                                              \
    return IDX_CONCAT(idx_read_, IDX_FNAME(TYPE))(element);                   \
}

IDX_GET_FN(UINT8)
IDX_GET_FN(INT8)
IDX_GET_FN(INT16)
IDX_GET_FN(INT32)
IDX_GET_FN(FLOAT)
IDX_GET_FN(DOUBLE)

#define IDX_SET_FN(TYPE)                                                      \
void IDX_CONCAT(idx_set_, IDX_FNAME(TYPE))(                                   \
    void *data, IDX_CTYPE(TYPE) value, int ndims, ...                         \
) {                                                                           \
    va_list indexes;                                                          \
    va_start(indexes, ndims);                                                 \
                                                                              \
    assert(idx_type(data) == IDX_TYPE(TYPE));                                 \
                                                                              \
    size_t offset = idx_data_offset_va(                                       \
        data, ndims, indexes                                                  \
    );                                                                        \
                                                                              \
    uint8_t *bytes = (uint8_t *) data;                                        \
    uint8_t *element = &bytes[                                                \
        4 + 4 * ndims +                                                       \
        offset * IDX_SIZE(TYPE)                                               \
    ];                                                                        \
                                                                              \
    IDX_CONCAT(idx_write_, IDX_FNAME(TYPE))(value, element);                  \
}

IDX_SET_FN(UINT8)
IDX_SET_FN(INT8)
IDX_SET_FN(INT16)
IDX_SET_FN(INT32)
IDX_SET_FN(FLOAT)
IDX_SET_FN(DOUBLE)

