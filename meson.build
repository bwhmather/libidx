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
  'idx_size': [
    'uint8_0d',
    'int8_0d',
    'int16_0d',
    'int32_0d',
    'float_0d',
    'double_0d',
    'max_uint8',
    'overflow_header_uint8',
    'overflow_bounds_uint8',
  ],
  'idx_type': [
    'double',
    'float',
    'int16',
    'int32',
    'int8',
    'uint8',
    'unknown',
  ],
  'idx_validate': [
    'too_short_for_header',
    'too_short_for_bounds',
    'too_short_for_data_1d',
    'too_short_for_data_3d',
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
    test(suite + ':' + test_name, test_exe)
  endforeach
endforeach
