
#ifndef __JG_DATA_TYPES_DEF_H__
#define __JG_DATA_TYPES_DEF_H__
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


// LINUX中      GCC类型长度(字节)
// type         x86_sizeof(type)    x64_sizeof(type)
// char         1                   1
// short        2                   2
// int          4                   4
// long         4                   8
// void*        4                   8
// long long    8                   8
// float        4                   4
// double       8                   8

//windows       VC编译器
// type         x86_sizeof(type)    x64_sizeof(type)
// char         1                   1
// short        2                   2
// int          4                   4
// long         4                   4
// void*        4                   8
// long long    8                   8
// float        4                   4
// double       8                   8


///< 基本数据类型定义
typedef char					T_I08;
typedef unsigned char			T_U08;

typedef short 					T_I16;
typedef unsigned short   		T_U16;

typedef int						T_I32;
typedef unsigned int			T_U32;

typedef int64_t					T_I64;
typedef uint64_t				T_U64;

typedef float					T_F32;
typedef double					T_F64;


#ifdef __cplusplus
}
#endif

#endif//__JG_DATA_TYPES_DEF_H__