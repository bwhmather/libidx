#pragma once

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

#include <stdint.h>
#include <stddef.h>

typedef enum {
    IDX_NO_ERROR = 0,
    // Indicates that the buffer in which an idx data-structure is meant to be
    // stored is shorter than needed.
    IDX_ERROR_TRUNCATED,
    // Indicates that the buffer in which an idx data-structure is stored
    // is too big, and contains extra data at the end.
    IDX_ERROR_OVERALLOCATED,
    // Indicates that the two empty bytes at the beginning of the structure
    // contain something other than zeroes.
    IDX_ERROR_BAD_PADDING,
    // Indicates that the idx data-structure contains values of an unsupported
    // type.
    IDX_ERROR_UNKNOWN_TYPE_CODE,
    // Indicates that the length of the data-structure exceeds what can be
    // represented by a `size_t`.
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
size_t idx_size(idx_type_t type, int ndims, ...);

/**
 * Writes an idx header with the given settings to `data` and clears the
 * remaining space.  The amount of memory that this function requires can be
 * figured out by calling `idx_size` with the same settings.
 */
void idx_init(void *data, idx_type_t type, int ndims, ...);

/**
 * Checks that `data` points to a consistent idx structure that takes up `len`
 * bytes.  If validation passes then any further operations on the structure
 * with matching settings should always succeed.
 */
idx_error_t idx_validate(const void *data, size_t len);

/**
 * Returns a pointer to a static null terminated string containing the human
 * readable name for a particular error code.  If the error code is not
 * recognized will return "unknown error".  All strings are noun phrases with
 * no capitalisation and no terminating full stop or newline.
 */
const char *idx_error_string(idx_error_t error);

/**
 * Functions to retrieve a value at a given index in the idx structure.
 * These do not verify that the structure is valid.  All getters will abort if
 * the type or number of dimensions do not match, or if the requested element
 * is out of bounds.
 */
uint8_t idx_get_uint8(const void *data, int ndims, ...);
int8_t idx_get_int8(const void *data, int ndims, ...);
int16_t idx_get_int16(const void *data, int ndims, ...);
int32_t idx_get_int32(const void *data, int ndims, ...);
float idx_get_float(const void *data, int ndims, ...);
double idx_get_double(const void *data, int ndims, ...);

/**
 * Functions to overwrite elements in an idx data-structure with new data.
 * These functions do not verify that `data` is a valid idx structure.
 * All setters will abort if their type does not match the type of the idx
 * structure, or if the `ndims` does not match the actual number of dimensions.
 * do not match those requested, or if the requested element is out of bounds.
 */
void idx_set_uint8(void *data, uint8_t value, int ndims, ...);
void idx_set_int8(void *data, int8_t value, int ndims, ...);
void idx_set_int16(void *data, int16_t value, int ndims, ...);
void idx_set_int32(void *data, int32_t value, int ndims, ...);
void idx_set_float(void *data, float value, int ndims, ...);
void idx_set_double(void *data, double value, int ndims, ...);

