﻿/*************************************************
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

//创建一个空白的图片类
Mat MatCreate(u8* filepath,u16 width,u16 height,u8 type)
{
    Mat mat;
    mat.bmi.biBitCount=type*8;
    mat.bmi.biSize=sizeof(BITMAPINFOHEADER);
    mat.width=width;
    mat.bmi.biWidth=width;
    mat.highth=height;
    mat.bmi.biHeight=height;
    mat.bmi.biPlanes=1;
    mat.bmi.biCompression=0;
    mat.bmi.biSizeImage=height*width*type;
    mat.bmi.biClrUsed=0;
    mat.bmi.biClrImportant=0;
    mat.bmi.biXPelsPerMeter=2874;
    mat.bmi.biYPelsPerMeter=2874;

    mat.bmf.bfType=((u16)'M'<<8)+'B';
    mat.bmf.bfSize=786486;
    mat.bmf.bfOffBits=54;
    mat.imgData=Li_malloc(height*width*type);
    mat.PATH=Li_malloc(100);
    strcpy(mat.PATH,filepath);
    return mat;
}



#ifdef WINDOWS

void Mat_Init()
{
    show=ShowbmpImage;
    at=bmpat;
    process=bmpprocess;
    load=bmpload;
    save=SaveAsbmpImage;
    destory=bmpdestory;
    copy=bmpcopy;
    create=MatCreate;
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

void Mat_Init()
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

void Mat_Init()
{
    show=ShowbmpImage;
    at=bmpat;
    process=bmpprocess;
    load=bmpload;
    save=SaveAsbmpImage;
    copy=bmpcopy;
    Li_malloc=malloc;
    Li_memcpy=memcpy;
    Li_free=free;
}


#endif

#ifdef ARM_NONE

#endif




