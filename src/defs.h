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