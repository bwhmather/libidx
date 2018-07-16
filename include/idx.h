#pragma once

#include <stdint.h>
#include <stddef.h>

typedef enum {
    IDX_NO_ERROR = 0,
    IDX_ERROR_TRUNCATED,
    IDX_ERROR_BAD_PADDING,
    IDX_ERROR_UNKNOWN_TYPE_CODE,
    IDX_ERROR_OVERFLOW,
} idx_error_t;

typedef enum {
    IDX_TYPE_UINT8 = 0x08,
    IDX_TYPE_INT8 = 0x09,
    IDX_TYPE_INT16 = 0x0B,
    IDX_TYPE_INT32 = 0x0C,
    IDX_TYPE_FLOAT = 0x0D,
    IDX_TYPE_DOUBLE = 0x0E,
} idx_type_t;

/**
 * Returns the type code of the idx structure pointed to by `data`.
 * Expects that `data` points to a validated idx structure.
 */
idx_type_t idx_type(const void *data);

/**
 * Returns the number of dimensions of that information stored in `data`.
 * Expects that `data` points to a validated idx structure.
 */
uint8_t idx_ndims(const void *data);

/**
 * Returns the extent of the data in a given dimension.
 * Does not verify that `data` is a valid idx structure.
 * Will abort the process if the data contains fewer than `dim` dimensions.
 */
size_t idx_bound(const void *data, uint8_t dim);

/**
 * Calculates the number of bytes required to store an idx data-structure with
 * the requested settings.  Will return 0 if the number exceeds what can be
 * represented by `size_t`.  Should be called to figure out how much space to
 * allocate before calling `idx_init`.
 */
size_t idx_size(idx_type_t type, uint8_t ndims, ...);

/**
 * Writes an idx header with the given settings to `data` and clears the
 * remaining space.  The amount of memory that this function requires can be
 * figured out by calling `idx_size` with the same settings.
 */
void idx_init(void *data, idx_type_t type, uint8_t ndims, ...);

/**
 * Checks that `data` points to a consistent idx structure that takes up `len`
 * bytes.  If validation passes then any further operations on the structure
 * with matching settings should always succeed.
 */
idx_error_t idx_validate(const void *data, size_t len);

const char *idx_error_string(idx_error_t error);

/**
 * Functions to retrieve a value at a given index in the idx structure.
 * These do not verify that the structure is valid.  All getters will abort if
 * the type or number of dimensions do not match, or if the requested element
 * is out of bounds.
 */
uint8_t idx_get_uint8(const void *data, uint8_t ndims, ...);
int8_t idx_get_int8(const void *data, uint8_t ndims, ...);
int16_t idx_get_int16(const void *data, uint8_t ndims, ...);
int32_t idx_get_int32(const void *data, uint8_t ndims, ...);
float idx_get_float(const void *data, uint8_t ndims, ...);
double idx_get_double(const void *data, uint8_t ndims, ...);

/**
 * Functions to overwrite elements in an idx data-structure with new data.
 * These functions do not verify that `data` is a valid idx structure.
 * All setters will abort if their type does not match the type of the idx
 * structure, or if the `ndims` does not match the actual number of dimensions.
 * do not match those requested, or if the requested element is out of bounds.
 */
void idx_set_uint8(void *data, uint8_t value, uint8_t ndims, ...);
void idx_set_int8(void *data, int8_t value, uint8_t ndims, ...);
void idx_set_int16(void *data, int16_t value, uint8_t ndims, ...);
void idx_set_int32(void *data, int32_t value, uint8_t ndims, ...);
void idx_set_float(void *data, float value, uint8_t ndims, ...);
void idx_set_double(void *data, double value, uint8_t ndims, ...);

