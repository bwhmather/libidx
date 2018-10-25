======
LibIDX
======

|build-status| |coverage|

A C library for reading and writing files in the IDX format, as used for the `MNIST data-set`_.


Usage
=====

Initializing a new IDX structure
--------------------------------

Libidx does not allocate memory.

.. code:: c

   size_t idx_size(idx_type_t type, int ndims, ...);

Calculates the number of bytes required to store an idx data-structure with
the requested settings.  Will return 0 if the number exceeds what can be
represented by `size_t`.  Should be called to figure out how much space to
allocate before calling `idx_init`.

.. code:: c

   void idx_init(void *data, idx_type_t type, int ndims, ...);

Writes an idx header with the given settings to `data` and clears the
remaining space.  The amount of memory that this function requires can be
figured out by calling `idx_size` with the same settings.


Loading an existing IDX structure
---------------------------------

.. code:: c

   idx_error_t idx_validate(const void *data, size_t len);

Checks that `data` points to a consistent idx structure that takes up `len`
bytes.  If validation passes then any further operations on the structure
with matching settings should always succeed.

.. code:: c
   const char *idx_error_string(idx_error_t error);

Returns a pointer to a static null terminated string containing the human
readable name for a particular error code.  If the error code is not
recognized will return "unknown error".  All strings are noun phrases with
no capitalisation and no terminating full stop or newline.


Possible errors:
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


Reading and writing
-------------------

Once a structure is constructed or validated it is assumed to be correct.
Any data issues detected after this will result in `libidx` calling ``abort``.
`libidx` does not provide any way to modify an IDX data-structure that would
affect its integrity, i.e. metadata is read-only, so it should never abort if
used correctly.


Reading metadata
````````````````
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

Returns the extent of the data in a given dimension.
Does not verify that `data` is a valid idx structure.
Will abort the process if the data contains fewer than `dim` dimensions.


Reading and writing values
``````````````````````````

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
