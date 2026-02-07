#include <stdint.h>

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

#define MIN(a, b) (((a) < (b) ? (a) : (b)))
#define MAX(a, b) (((a) > (b) ? (a) : (b)))
#define CLAMP(a, b, c) (((b) > (c) ? (c) : (((b) < (a)) ? (a) : (b))))

typedef double Matrix4[16];
typedef double Matrix3[9];
typedef double Matrix2[4];

typedef struct {
    double x;
    double y;
    double z;
} Vec4;

typedef struct {
    double x;
    double y;
    double z;
} Vec3;


typedef struct {
    double x;
    double y;
} Vec2;
