#ifndef _CV_H
#define _CV_H

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
#define bool                 u8
#define false                0
#define true                 1  

//选择使用平台
#define WINDOWS

#ifdef WINDOWS
// inline CVInit(Mat mat)
// {  

// }
#endif



#ifdef X86_LINUX
// inline CVInit(Mat mat)
// {  

// }

#endif

#ifdef ARM_LINUX
// inline CVInit(Mat mat)
// {  

// }
#endif

#ifdef ARM_NONE
// inline CVInit(Mat mat)
// {  

// }
#endif


#endif // !CV_H