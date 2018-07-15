#include "idx.h"

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <assert.h>

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


static size_t idx_type_size(idx_type_t type) {
    switch (type) {
    case IDX_TYPE_UINT8:
        return 1;
    case IDX_TYPE_INT8:
        return 1;
    case IDX_TYPE_INT16:
        return 2;
    case IDX_TYPE_INT32:
        return 4;
    case IDX_TYPE_FLOAT:
        return 4;
    case IDX_TYPE_DOUBLE:
        return 8;
    default:
        assert(false);
    }
}

static inline uint8_t idx_read_uint8(const char bytes[1]) {
    return (uint8_t) bytes[0];
}

static inline int8_t idx_read_int8(const char bytes[1]) {
    return (int8_t) bytes[0];
}

static inline uint16_t idx_read_uint16(const char bytes[2]) {
    return (
        ((uint16_t) bytes[0] << 8) |
        ((uint16_t) bytes[1] << 0)
    );
}

static inline int16_t idx_read_int16(const char bytes[4]) {
    return (int16_t) idx_read_uint16(bytes);
}

static inline uint32_t idx_read_uint32(const char bytes[4]) {
    return (
        ((uint32_t) bytes[0] << 24) |
        ((uint32_t) bytes[1] << 16) |
        ((uint32_t) bytes[2] << 8) |
        ((uint32_t) bytes[3] << 0)
    );
}

static inline int32_t idx_read_int32(const char bytes[4]) {
    return (int32_t) idx_read_uint32(bytes);
}

static inline float idx_read_float(const char bytes[4]) {
    return (float) idx_read_uint32(bytes);
}

static inline double idx_read_double(const char bytes[8]) {
    return (double) (
        ((uint64_t) bytes[0] << 56) |
        ((uint64_t) bytes[1] << 48) |
        ((uint64_t) bytes[2] << 40) |
        ((uint64_t) bytes[3] << 32) |
        ((uint64_t) bytes[4] << 24) |
        ((uint64_t) bytes[5] << 16) |
        ((uint64_t) bytes[6] << 8) |
        ((uint64_t) bytes[7] << 0)
    );
}

static inline void idx_write_uint8(uint8_t value, char bytes[1]) {
    bytes[0] = (char) value;
}

static inline void idx_write_int8(int8_t value, char bytes[1]) {
    bytes[0] = (char) value;
}

static inline void idx_write_uint16(uint16_t value, char bytes[2]) {
    bytes[0] = (0xff00 & value) >> 8;
    bytes[1] = (0x00ff & value) >> 0;
}

static inline void idx_write_int16(int16_t value, char bytes[2]) {
    idx_write_uint16((uint16_t) value, bytes);
}

static inline void idx_write_uint32(uint32_t value, char bytes[4]) {
    bytes[0] = (0xff000000 & value) >> 24;
    bytes[1] = (0x00ff0000 & value) >> 16;
    bytes[2] = (0x0000ff00 & value) >> 8;
    bytes[3] = (0x000000ff & value) >> 0;
}

static inline void idx_write_int32(int32_t value, char bytes[4]) {
    idx_write_uint32((uint32_t) value, bytes);
}

static inline void idx_write_float(float value, char bytes[4]) {
    idx_write_uint32((float) value, bytes);
}

static inline void idx_write_double(double value, char bytes[8]) {
    bytes[0] = (0xff00000000000000 & (uint64_t) value) >> 56;
    bytes[1] = (0x00ff000000000000 & (uint64_t) value) >> 48;
    bytes[2] = (0x0000ff0000000000 & (uint64_t) value) >> 40;
    bytes[3] = (0x000000ff00000000 & (uint64_t) value) >> 32;
    bytes[4] = (0x00000000ff000000 & (uint64_t) value) >> 24;
    bytes[5] = (0x0000000000ff0000 & (uint64_t) value) >> 16;
    bytes[6] = (0x000000000000ff00 & (uint64_t) value) >> 8;
    bytes[7] = (0x00000000000000ff & (uint64_t) value) >> 0;
}

idx_type_t idx_type(const char *data) {
    return (idx_type_t) data[2];
}

uint8_t idx_ndims(const char *data) {
    return data[3];
}

size_t idx_bound(const char *data, uint8_t dim) {
    assert(dim < idx_ndims(data));
    return (size_t) idx_read_uint32(data + 4 + 4 * dim);
}

size_t idx_size(idx_type_t type, uint8_t ndims, ...) {
    // Magic number.
    size_t header_size = 4;
    
    // Space required to store the size of each dimension.
    header_size += 4 * ndims;

    va_list bounds;
    va_start(bounds, ndims);

    size_t data_size = idx_type_size(type);
    for (int dim = 0; dim < ndims; dim++) {
        uint32_t bound = va_arg(bounds, uint32_t);
        if (SIZE_MAX / bound > data_size) {
            return 0;
        }
        data_size *= bound;
    }

    if ((SIZE_MAX - header_size) < data_size) {
        return 0;
    }

    return header_size + data_size;
}

void idx_init(char *data, idx_type_t type, uint8_t ndims, ...) {
    idx_write_uint16(0, &data[0]);
    idx_write_uint8(type, &data[2]);
    idx_write_uint8(ndims, &data[3]);

    va_list bounds;
    va_start(bounds, ndims);

    size_t data_size = idx_type_size(type);
    for (int dim = 0; dim < ndims; dim++) {
        uint32_t bound = va_arg(bounds, uint32_t);
        assert(SIZE_MAX / bound <= data_size);
        idx_write_uint32(bound, &data[4 + 4 * dim]);
    }

    assert((SIZE_MAX - data_size) >= 4);
}

idx_error_t idx_validate(const char *data, size_t size) {
    // Check that length is long enough to contain magic number.
    if (size < 4) {
        return IDX_ERROR_TRUNCATED;
    }
    
    // Parse the header.
    uint16_t magic = idx_read_uint16(&data[0]);
    idx_type_t type = (idx_type_t) idx_read_uint8(&data[2]);
    uint8_t ndims = idx_read_uint8(&data[3]);

    // Check that the first two bytes are zero.
    if (magic != 0) {
        return IDX_ERROR_BAD_PADDING;
    }

    // Check type code is valid.
    if (
        type != IDX_TYPE_UINT8 &&
        type != IDX_TYPE_INT8 &&
        type != IDX_TYPE_INT16 &&
        type != IDX_TYPE_INT32 &&
        type != IDX_TYPE_FLOAT &&
        type != IDX_TYPE_DOUBLE
    ) {
        return IDX_ERROR_UNKNOWN_TYPE_CODE;
    }

    // Check that there is at least enough space to store the dimensions.
    if (size < 4 + (size_t) ndims * 4) {
        return IDX_ERROR_TRUNCATED;
    }

    // Check length.
    size_t expected_length = 1;
    for (int dim = 0; dim < ndims; dim++) {
        uint32_t bound = idx_read_uint32(&data[4 + (4 * dim)]);
        if (SIZE_MAX / bound > expected_length) {
            return IDX_ERROR_OVERFLOW;
        }
        expected_length *= bound;
    }

    return IDX_NO_ERROR;
}

const char *idx_error_string(idx_error_t error) {
    switch (error) {
    case IDX_NO_ERROR:
        return "no error";
    case IDX_ERROR_TRUNCATED:
        return "truncated";
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
    const char *data, uint8_t ndims, va_list indexes
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
    const char *data, uint8_t ndims, ...                                      \
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
    const char *ptr = &data[                                                  \
        4 + 4 * ndims +                                                       \
        offset * IDX_SIZE(TYPE)                                               \
    ];                                                                        \
                                                                              \
    return IDX_CONCAT(idx_read_, IDX_FNAME(TYPE))(ptr);                       \
}

IDX_GET_FN(UINT8)
IDX_GET_FN(INT8)
IDX_GET_FN(INT16)
IDX_GET_FN(INT32)
IDX_GET_FN(FLOAT)
IDX_GET_FN(DOUBLE)

#define IDX_SET_FN(TYPE)                                                      \
void IDX_CONCAT(idx_set_, IDX_FNAME(TYPE))(                                   \
    char *data, IDX_CTYPE(TYPE) value, uint8_t ndims, ...                     \
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
    char *ptr = &data[                                                        \
        4 + 4 * ndims +                                                       \
        offset * IDX_SIZE(TYPE)                                               \
    ];                                                                        \
                                                                              \
    IDX_CONCAT(idx_write_, IDX_FNAME(TYPE))(value, ptr);                      \
}

IDX_SET_FN(UINT8)
IDX_SET_FN(INT8)
IDX_SET_FN(INT16)
IDX_SET_FN(INT32)
IDX_SET_FN(FLOAT)
IDX_SET_FN(DOUBLE)

