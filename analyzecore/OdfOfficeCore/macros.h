#pragma once


#include <stddef.h>

#ifndef SAL_N_ELEMENTS
#    if defined(__cplusplus) && ( defined(__GXX_EXPERIMENTAL_CXX0X__) || __cplusplus >= 201103L )
/*
* Magic template to calculate at compile time the number of elements
* in an array. Enforcing that the argument must be a array and not
* a pointer, e.g.
*  char *pFoo="foo";
*  SAL_N_ELEMENTS(pFoo);
* fails while
*  SAL_N_ELEMENTS("foo");
* or
*  char aFoo[]="foo";
*  SAL_N_ELEMENTS(aFoo);
* pass
*
* Unfortunately if arr is an array of an anonymous class then we need
* C++0x, i.e. see
* http://www.open-std.org/jtc1/sc22/wg21/docs/cwg_defects.html#757
*/
template <typename T, size_t S> char(&sal_n_array_size(T(&)[S]))[S];
#        define SAL_N_ELEMENTS(arr)     (sizeof(sal_n_array_size(arr)))
#    else
#        define SAL_N_ELEMENTS(arr)     (sizeof (arr) / sizeof ((arr)[0]))
#    endif
#endif

#ifndef SAL_BOUND
#    define SAL_BOUND(x,l,h)        ((x) <= (l) ? (l) : ((x) >= (h) ? (h) : (x)))
#endif

#ifndef SAL_ABS
#    define SAL_ABS(a)              (((a) < 0) ? (-(a)) : (a))
#endif

#ifndef SAL_STRINGIFY
#   define SAL_STRINGIFY_ARG(x) #x
#   define SAL_STRINGIFY(x) SAL_STRINGIFY_ARG(x)
#endif

#define XML_CAST( str ) reinterpret_cast< const sal_Char* >( str )
