#ifndef _TYPES_H_
#define _TYPES_H_

typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef signed long long s64;

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef float f32;
typedef double f64;

#define NULL ((void *)0)

#if !defined(__cplusplus)
typedef int bool;
#define true 1
#define false 0
#endif

#endif
