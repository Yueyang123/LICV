/*
*版权所有 (C)2019,Yueyang.
*文件名称：Mat.c
*内容摘要：LiteCV基础数据类型Mat实现
*当前版本：V1.0
*作者：杨越
*完成日期：20191020
*/

#include "bmp.h"
#include "cv.h"
#include <string.h>
#include <stdlib.h>

//选择使用平台
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




