#include <stdint.h>
#include <stddef.h>

typedef enum {
    IDX_NO_ERROR = 0,
    IDX_ERROR_TRUNCATED,
    IDX_ERROR_BAD_HEADER,
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

idx_type_t idx_type(const char *data);
uint8_t idx_ndims(const char *data);
size_t idx_bound(const char *data, uint8_t dim);

idx_error_t idx_size(size_t *size, idx_type_t type, uint8_t ndims, ...);
void idx_init(char *data, idx_type_t type, uint8_t ndims, ...);

idx_error_t idx_validate(const char *data, size_t len);

uint8_t idx_get_uint8(const char *data, uint8_t ndims, ...);
int8_t idx_get_int8(const char *data, uint8_t ndims, ...);
int16_t idx_get_int16(const char *data, uint8_t ndims, ...);
int32_t idx_get_int32(const char *data, uint8_t ndims, ...);
float idx_get_float(const char *data, uint8_t ndims, ...);
double idx_get_double(const char *data, uint8_t ndims, ...);

void idx_set_uint8(char *data, uint8_t value, uint8_t ndims, ...);
void idx_set_int8(char *data, int8_t value, uint8_t ndims, ...);
void idx_set_int16(char *data, int16_t value, uint8_t ndims, ...);
void idx_set_int32(char *data, int32_t value, uint8_t ndims, ...);
void idx_set_float(char *data, float value, uint8_t ndims, ...);
void idx_set_double(char *data, double value, uint8_t ndims, ...);




