/*************************************************
Copyright © Yueyang Co. Ltd. 2019-2029. All rights reserved.
File name: bmp.h
Author： Yueyang
Version: V1.0
Description: 提供对于bmp文件的操作函数
Others: 
Log: 11.3 Yueyang
*************************************************/

#ifndef BMP_H_INCLUDED
#define BMP_H_INCLUDED
#include "stdio.h"
#include "Mat.h"

//通配指针提供，跨平台主要的实现方式
 void   (*Li_free)   (void *_Memory);
 void * (*Li_malloc) (size_t _Size);
 void * (*Li_memcpy) (void * _Dst,const void * _Src,size_t _Size);
 void   (*show)      (Mat* mat);
 u8*    (*at)        (Mat* mat,int width,int highth);
 int    (*process)   (Mat* mat,int x,int y,u32 color);
 Mat    (*load)      (char *filepath);
 int    (*save)      (char *filepath,Mat* mat);
 Mat    (*copy)      (Mat mat);
 void   (*destory)   (Mat* mat);
 Mat    (*create) (u8* filepath,u16 width,u16 height,u8 type);


//检查路径是否合法
int CheckbmpFilePath(char *filepath);
//读BMP文件头
int ReadbmpFileHeader(char *filepath,BITMAPFILEHEADER *bmfh);
//打印BMP文件头
void PrintbmpFileHeader(BITMAPFILEHEADER *bmfh);
//读BMP信息头
int ReadbmpInfoHeader(char *filepath,BITMAPINFOHEADER *bmih);
//打印BMP信息头
void PrintbmpInfoHeader(BITMAPINFOHEADER *bmih);
//读取BMP的图像数据
int ReadbmpPixelData(char *filepath,BYTE *imgData);
//获取图像每一行所占用的字节数
LONG GetLineBytes(int imgWidth,int bitCount);
//打印位图数据信息
void PrintbmpPixelData(BYTE *imgData,int width,int height,int bitCount);
//提供一个MAT的结构体将其存储为BMP文件
int SaveAsbmpImage(char *filepath,Mat* mat);
//图片显示 注意在不同的硬件平台上需要重写这个函数

//加载BMP图片，并返回一个MAT结构体
Mat bmpload(char *filepath);
//对于图片的每一个像素分别操作
int bmpprocess(Mat* mat,int width,int highth,u32 color);
//获取BMP某个像素所在的地址
u8* bmpat(Mat* mat,int width,int highth);
//BMP拷贝函数
Mat bmpcopy(Mat mat);
//析构函数
void bmpdestory(Mat* mat);



#endif 







