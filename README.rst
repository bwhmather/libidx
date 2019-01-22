======
LibIDX
======

|build-status| |coverage|

A C library for reading and writing multi-dimensional arrays stored in the
IDX format.

The IDX format is used for distributing the `MNIST data-set`_.


Usage
=====

`libidx` operates on `void` pointers to a region of memory.
Memory can be either unvalidated or uninitialized.


`libidx` should be used in three phases.
In the first phase one shoud

In the first phase ... should be used to ensure that the structure is valid.
The metadata functions should then be used to ensure that the data has the
expected type, number of dimensions, and bounds.
Once that is done 

If used correctly, it should be impossible to trigger an ``abort`` or read or
write from uninitialized memory.







The first group take a pointer to a region of unvalidated memory and either
validate it, or initialize it.  If these functions do not report any errors,
the memory can be treated as valid and passed to the second group.

First a pointer to an area of memory must be

Initializing a new IDX structure
--------------------------------

`libidx` does not allocate memory.  Instead it provides the `idx_size` function
which will calculate and return the number of bytes required to store an idx
data-structure with the requested settings.  Users should call `idx_size`,
allocate a file or buffer of the suggested size, then initialize it using
`idx_init`.

.. code:: c

   size_t idx_size(idx_type_t type, int ndims, ...);

`idx_size` will return 0 if the number exceeds what can be represented by
`size_t`.  There are no other possible errors.


The signature of `idx_init` is almost the same as `idx_size` except that it
takes a pointer to an uninitialized buffer as its first argument.

.. code:: c

   void idx_init(void *data, idx_type_t type, int ndims, ...);


Writes an idx header with the given settings to `data` and clears the
remaining space.


Loading an existing IDX structure
---------------------------------

.. code:: c

   idx_error_t idx_validate(const void *data, size_t len);

Checks that `data` points to a consistent idx structure that takes up `len`
bytes.  If validation passes then any further operations on the structure
with matching settings should always succeed.

Currently exported error codes:
  - ``IDX_NO_ERROR``: The 
  - ``IDX_ERROR_TRUNCATED``: Indicates that the buffer in which an idx
    data-structure is meant to be stored is shorter than needed.
  - ``IDX_ERROR_OVERALLOCATED``: Indicates that the buffer in which an idx
    data-structure is stored is too big, and contains extra data at the end.
  - ``IDX_ERROR_BAD_PADDING``: Indicates that the two empty bytes at the
    beginning of the structure contain something other than zeroes.
  - ``IDX_ERROR_UNKNOWN_TYPE_CODE``: Indicates that the idx data-structure
    contains values of an unsupported type.
  - ``IDX_ERROR_OVERFLOW``: Indicates that the length of the data-structure
    exceeds what can be represented by a `size_t`.

It is assumed that callers will check for ``IDX_NO_ERROR`` instead of trying to
handle error codes individually.  Error codes indicate a problem with the data
and 

These all indicate 


.. code:: c
   const char *idx_error_string(idx_error_t error);

Returns a pointer to a static null terminated string containing the human
readable name for a particular error code.  If the error code is not
recognized will return "unknown error".  All strings are noun phrases with
no capitalisation and no terminating full stop or newline.

Reading and writing
-------------------

Once a structure is constructed or validated it is assumed to be correct.
Any data issues detected after this will result in `libidx` calling ``abort``.
`libidx` does not provide any way to modify an IDX data-structure that would
affect its integrity, i.e. metadata is read-only, so it should never abort if
used correctly.


Reading metadata
````````````````
Functions for reading metadata assume that the data-structure has been checked
using `idx_validate`, or constructed using `idx_init`.

.. code:: c
   typedef enum {
       IDX_TYPE_UINT8 = 0x08,
       IDX_TYPE_INT8 = 0x09,
       IDX_TYPE_INT16 = 0x0B,
       IDX_TYPE_INT32 = 0x0C,
       IDX_TYPE_FLOAT = 0x0D,
       IDX_TYPE_DOUBLE = 0x0E,
   } idx_type_t;

   idx_type_t idx_type(const void *data);

Returns the type code of the idx structure pointed to by `data`.
Expects that `data` points to a validated idx structure.

.. code:: c

   uint8_t idx_ndims(const void *data);

Returns the number of dimensions of that information stored in `data`.
Expects that `data` points to a validated idx structure.

.. code:: c

   size_t idx_bound(const void *data, uint8_t dim);

Returns the extent of the data in the given dimension.
Does not verify that `data` is a valid idx structure.
Will abort the process if the data contains fewer than `dim` dimensions.  To
avoid this, the number of dimensions should be checked in advance using
`idx_ndims`.


Reading and writing values
``````````````````````````
`libidx` provides a collection of variadic functions for reading and writing
values.

All functions expect a pointer to an idx data structure, an int containing the
number of dimensions, and a number of integer indices.

These assume that the type of the values stored in the data-structure, and the
number of dimensions are known statically.


The `ndims` parameter should be considered static.  If `libidx` was written in
`C++` then `ndims` would be a template parameter.  `ndims` must have a value
equal to the number of arguments that follow it.

The type is similarly static, but is passed to `libidx` by calling a different
specialisation.

Calling a function with the wrong type, passing the wrong number of indices,
or passing an index that exceeds the bounds of the corresponding dimension will
cause `libidx` to abort the process.  These constraints can all be checked in
advance so there is no excuse.

.. code:: c

   uint8_t idx_get_uint8(const void *data, int ndims, ...);
   int8_t idx_get_int8(const void *data, int ndims, ...);
   int16_t idx_get_int16(const void *data, int ndims, ...);
   int32_t idx_get_int32(const void *data, int ndims, ...);
   float idx_get_float(const void *data, int ndims, ...);
   double idx_get_double(const void *data, int ndims, ...);

Functions to retrieve a value at a given index in the idx structure.
These do not verify that the structure is valid.  All getters will abort if
the type or number of dimensions do not match, or if the requested element
is out of bounds.

.. code:: c

   void idx_set_uint8(void *data, uint8_t value, int ndims, ...);
   void idx_set_int8(void *data, int8_t value, int ndims, ...);
   void idx_set_int16(void *data, int16_t value, int ndims, ...);
   void idx_set_int32(void *data, int32_t value, int ndims, ...);
   void idx_set_float(void *data, float value, int ndims, ...);
   void idx_set_double(void *data, double value, int ndims, ...);

Functions to overwrite elements in an idx data-structure with new data.
These functions do not verify that `data` is a valid idx structure.
All setters will abort if their type does not match the type of the idx
structure, or if the `ndims` does not match the actual number of dimensions.
do not match those requested, or if the requested element is out of bounds.


License
-------

The project is made available under the MIT license.  See `LICENSE`_ for details.


.. |build-status| image:: https://travis-ci.org/bwhmather/libidx.png?branch=develop
    :target: https://travis-ci.org/bwhmather/libidx
    :alt: Build Status
.. |coverage| image:: https://coveralls.io/repos/bwhmather/libidx/badge.png?branch=develop
    :target: https://coveralls.io/r/bwhmather/libidx?branch=develop
    :alt: Coverage
.. _MNIST data-set: http://yann.lecun.com/exdb/mnist/
.. _LICENSE: ./LICENSE
