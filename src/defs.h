typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef signed char i8;
typedef signed short i16;
typedef signed int i32;
typedef signed long long i64;

typedef float f32;
typedef double f64;

typedef int b32;

// Inline
#ifdef _MSC_VER
#define ZINLINE __forceinline
#define ZNOINLINE __declspec(noinline)
#else
#define ZINLINE static inline
#define ZNOINLINE
#endif

#define VIRTUAL_WIDTH 640
#define VIRTUAL_HEIGHT 360
#define PIXEL_SCALE 3

#define WINDOW_WIDTH (VIRTUAL_WIDTH * PIXEL_SCALE)    // e.g., 320 * 4 = 1280
#define WINDOW_HEIGHT (VIRTUAL_HEIGHT * PIXEL_SCALE) // e.g., 180 * 4 = 720

#define BIT(x) 1 << (x)
#define KB(x) ((unsigned long long)1024 * x)
#define MB(x) ((unsigned long long)1024 * KB(x))
#define GB(x) ((unsigned long long)1024 * MB(x))