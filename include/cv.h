/*
*��Ȩ���� (C)2019,Yueyang.
*�ļ����ƣ�cv.h
*����ժҪ��LiteCV����ͷ�ļ�
*��ǰ�汾��V1.0
*���ߣ���Խ
*������ڣ�20191020
*/


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
#define PI                   3.1415926 

//ѡ��ʹ��ƽ̨
#define WINDOWS

#ifdef WINDOWS



#endif



#ifdef X86_LINUX


#endif

#ifdef ARM_LINUX

#endif

#ifdef ARM_NONE

#endif


#endif // !CV_H