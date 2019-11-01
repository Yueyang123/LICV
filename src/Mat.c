/*
*��Ȩ���� (C)2019,Yueyang.
*�ļ����ƣ�Mat.c
*����ժҪ��LiteCV������������Matʵ��
*��ǰ�汾��V1.0
*���ߣ���Խ
*������ڣ�20191020
*/

#include "bmp.h"
#include "cv.h"
#include <string.h>
#include <stdlib.h>

//ѡ��ʹ��ƽ̨
#define WINDOWS


#ifdef WINDOWS

void Mat_INIT()
{
    show=ShowbmpImage;
    at=bmpat;
    process=bmpprocess;
    load=bmpload;
    save=SaveAsbmpImage;
    copy=bmpcopy;
    fileread=fread;
    fileopen=fopen;
    fileseek=fseek;
    fileclose=fclose;
    Li_malloc=malloc;
    Li_memcpy=memcpy;
    Li_free=free;
}


#endif



#ifdef X86_LINUX

void Mat_INIT()
{
    show=ShowbmpImage;
    at=bmpat;
    process=bmpprocess;
    load=bmpload;
    save=SaveAsbmpImage;
    copy=bmpcopy;
    fileread=fread;
    fileopen=fopen;
    fileseek=fseek;
    fileclose=fclose;
    Li_malloc=malloc;
    Li_memcpy=memcpy;
    Li_free=free;
}


#endif

#ifdef ARM_LINUX

#endif

#ifdef ARM_NONE

#endif




