project('idx', 'c')

includes = include_directories('include')

### Library ###
lib_sources = [
  'src/idx.c',
]

lib = both_libraries(
  'idx', lib_sources,
  include_directories : includes,
  install : true,
)

### Tests ###
test_includes = include_directories('include', 'tests')

test_suites = {
  'idx_bound': [
    'unexpected_dim_1d',
  ],
  'idx_error_string': [
    'known',
    'unknown',
  ],
  'idx_get_uint8': [
    'valid_0d',
    'invalid_type_0d',
    'invalid_ndims_0d',
    'empty_1d',
    'large_1d',
    'empty_2d',
    'small_2d',
    'large_2d',
  ],
  'idx_set_double': [
    'pos_one_0d',
  ],
  'idx_init': [
    'double_0d',
    'float_0d',
    'int16_0d',
    'int32_0d',
    'int8_0d',
    'uint8_0d',
    'double_3d',
    'float_3d',
    'int16_3d',
    'int32_3d',
    'int8_3d',
    'uint8_3d',
    'unsupported_types',
  ],
  'idx_size': [
    'uint8_0d',
    'int8_0d',
    'int16_0d',
    'int32_0d',
    'float_0d',
    'double_0d',
    'max_uint8',
    'unsupported_0d',
    'overflow_uint8',
    'overflow_int16',
  ],
  'idx_type': [
    'double',
    'float',
    'int16',
    'int32',
    'int8',
    'uint8',
    'all',
  ],
  'idx_validate': [
    'uint8_0d',
    'uint8_2d',
    'too_short_for_header',
    'too_short_for_bounds',
    'too_short_for_data_1d',
    'too_short_for_data_3d',
    'overflow_uint8',
    'overflow_int16',
    'bad_padding',
  ],
  'idx_type_supported': [
    'double',
    'float',
    'int16',
    'int32',
    'int8',
    'uint8',
    'unknown',
  ],
}

foreach suite, tests : test_suites
  foreach test_name : tests
    test_exe = executable(
      'test-' + suite + '-' + test_name,
      'tests/' + suite + '/test_' + test_name + '.c',
      include_directories : test_includes,
      link_with : lib,
      install : false,
    )
    test(suite + ':' + test_name, test_exe, timeout: 180)
  endforeach
endforeach
