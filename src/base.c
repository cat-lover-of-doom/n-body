#include <stdint.h>
#include <stdlib.h>
#include <math.h>
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

typedef float Matrix4[16];
typedef float Matrix3[9];
typedef float Matrix2[4];

typedef struct {
    float x;
    float y;
    float z;
} Vec4;

typedef struct {
    float x;
    float y;
    float z;
} Vec3;

typedef struct {
    float x;
    float y;
} Vec2;

static inline Vec2 vec2_add(Vec2 a, Vec2 b) {
    return (Vec2){a.x + b.x, a.y + b.y};
}

static inline void vec2_add_inplace(Vec2 *v, Vec2 other) {
    v->x += other.x;
    v->y += other.y;
}

static inline Vec2 vec2_scale(Vec2 v, float scalar) {
    return (Vec2){v.x * scalar, v.y * scalar};
}

static inline void vec2_scale_inplace(Vec2 *v, float scalar) {
    v->x *= scalar;
    v->y *= scalar;
}

static inline float vec2_length(Vec2 v) {
    return sqrt(v.x * v.x + v.y * v.y);
}

static inline float vec2_dot(Vec2 a, Vec2 b) {
    return a.x * b.x + a.y * b.y;
}

static inline Vec2 vec2_sub(Vec2 a, Vec2 b) {
    return (Vec2){a.x - b.x, a.y - b.y};
}

static inline Vec2 vec2_normalize(Vec2 v) {
    float len = vec2_length(v);
    if (len < 1e-10) return (Vec2){0, 0};  // Avoid division by zero
    return vec2_scale(v, 1.0 / len);
}

static inline Vec3 vec3_add(Vec3 a, Vec3 b) {
    return (Vec3){a.x + b.x, a.y + b.y, a.z + b.z};
}

static inline void vec3_add_inplace(Vec3 *v, Vec3 other) {
    v->x += other.x;
    v->y += other.y;
    v->z += other.z;
}

static inline Vec3 vec3_scale(Vec3 v, float scalar) {
    return (Vec3){v.x * scalar, v.y * scalar, v.z * scalar};
}

static inline void vec3_scale_inplace(Vec3 *v, float scalar) {
    v->x *= scalar;
    v->y *= scalar;
    v->z *= scalar;
}

static inline float vec3_length(Vec3 v) {
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

static inline float vec3_dot(Vec3 a, Vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

static inline Vec3 vec3_sub(Vec3 a, Vec3 b) {
    return (Vec3){a.x - b.x, a.y - b.y, a.z - b.z};
}

static inline Vec3 vec3_normalize(Vec3 v) {
    float len = vec3_length(v);
    if (len < 1e-10f) return (Vec3){0, 0, 0};  // Avoid division by zero
    return vec3_scale(v, 1.0f / len);
}

static float frand01(void)
{
    return (float)rand() / (double)RAND_MAX;
}

float frand(double a, double b)
{
    return a + (b - a) * frand01();
}
