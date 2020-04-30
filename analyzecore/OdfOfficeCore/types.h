#pragma once

/* Boolean */
typedef unsigned char sal_Bool;
#   define sal_False ((sal_Bool)0)
#   define sal_True  ((sal_Bool)1)

/* char is assumed to always be 1 byte long */
typedef signed char         sal_Int8;
typedef unsigned char       sal_uInt8;

typedef signed short      sal_Int16;
typedef unsigned short    sal_uInt16;

typedef signed long       sal_Int32;
typedef unsigned long     sal_uInt32;


/** A legacy synonym for `char`.

@deprecated use plain `char` instead.
*/
typedef char sal_Char;

/** A legacy synonym for `signed char`.

@deprecated use plain `signed char` instead.
*/
typedef signed char sal_sChar;

/** A legacy synonym for `unsigned char`.

@deprecated use plain `unsigned char` instead.
*/
typedef unsigned char sal_uChar;

typedef wchar_t sal_Unicode;


#define SAL_CONSTEXPR