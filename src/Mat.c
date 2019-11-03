/*************************************************
Copyright © Yueyang Co. Ltd. 2019-2029. All rights reserved.
File name: Mat.c
Author： Yueyang
Version: V1.0
Description: 提供Mat结构体
Others: 
Log: 11.3 Yueyang
*************************************************/

#include "bmp.h"
#include "cv.h"
#include <string.h>
#include <stdlib.h>


#ifdef WINDOWS

void Mat_INIT()
{
    show=ShowbmpImage;
    at=bmpat;
    process=bmpprocess;
    load=bmpload;
    save=SaveAsbmpImage;
    destory=bmpdestory;
    copy=bmpcopy;
    filewrite=fwrite;
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




