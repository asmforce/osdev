/**
 * @project Andromeda
 * @author: Krutko Vitaliy
 * @aka: asmforce
 * @e-mail: asmforce@ukr.net
 * @copyright (C)
**/

#ifndef ANDROMEDA_ALIASES_HPP
#define ANDROMEDA_ALIASES_HPP

// C-style name mangling
#define CMANGLE extern "C"

#define GATTRIBUTE(x) __attribute__((x))
#define INLINE GATTRIBUTE(__always_inline__)
#define PACKED GATTRIBUTE(packed)
#define GASM __asm__
#define GVASM __asm__ __volatile__

// CHARACTER TYPES:
typedef char               tchar;
typedef wchar_t            wchar;

// SIGNED INTEGER TYPES:
typedef signed char        i8;
typedef signed short       i16;
typedef signed long        i32;
typedef signed long long   i64;

// UNSIGNED INTEGER TYPES:
typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned long      u32;
typedef unsigned long long u64;

// FLOATING POINT TYPES:
typedef long double        xdouble;

#endif // ANDROMEDA_ALIASES_HPP
