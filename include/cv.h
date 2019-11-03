/*************************************************
Copyright © Yueyang Co. Ltd. 2019-2029. All rights reserved.
File name: cv.h
Author： Yueyang
Version: V1.0
Description: LiteCV顶层头文件，提供基础数据类型
Others: 
Log: 11.3 Yueyang
*************************************************/

#ifndef _CV_H
#define _CV_H


#define bool                 u8
#define false                0
#define true                 1  
#define PI                   3.1415926 


#define WINDOWS


//在不同的平台上一些数据的字长不一样
#ifdef WINDOWS

typedef unsigned short       WORD;
typedef unsigned long        DWORD;
typedef long                 LONG;
typedef unsigned char        BYTE;
typedef unsigned             char uint8_t;
typedef unsigned short       int uint16_t;
typedef unsigned             int uint32_t;
typedef uint32_t             u32;
typedef uint16_t             u16;
typedef uint8_t              u8;

#endif



#ifdef X86_LINUX

typedef unsigned             char uint8_t;
typedef unsigned short       int uint16_t;
typedef unsigned             int uint32_t;
typedef uint32_t             u32;
typedef uint16_t             u16;
typedef uint8_t              u8;
typedef unsigned short       WORD;
typedef u32                  DWORD;
typedef u32                  LONG;
typedef unsigned char        BYTE;



#endif

#ifdef ARM_LINUX

#endif

#ifdef ARM_NONE

#endif


#endif // !CV_H