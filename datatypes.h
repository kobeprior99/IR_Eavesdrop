/* 
 * File:   datatypes.h
 * Author: http://pic18fxx.blogspot.com 
 */
#ifndef DATATYPES_H
#define	DATATYPES_H
//==============================================================================
// New name for data types.
//==============================================================================
typedef char                    S8;   // -128 to 127
typedef unsigned char           U8;   // 0 to 255
typedef const char              CS8;  // -128 to 127
typedef const unsigned char     CU8;  // 0 to 255
typedef volatile unsigned char  VU8;  // 0 to 255
typedef short					S16;  // -32768 to 32767
typedef unsigned short			U16;  // 0 to 65535
typedef const unsigned short	CU16; // 0 to 65535
typedef volatile unsigned short	VU16; // 0 to 65535
typedef int                     SI16; //-2147483648 to 2147483647
typedef unsigned int            UI32; // 0 to 4294967295
typedef float                   F32;  // 1.2E-38 to 3.4E+38
typedef char *SSTR8;
#endif	/* DATATYPES_H */
