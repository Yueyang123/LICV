/*
*版权所有 (C)2019,Yueyang.
*文件名称：bmp.h
*内容摘要：LiteCV bmp图片基本操作
*当前版本：V1.0
*作者：杨越
*完成日期：20191020
*/

#ifndef BMP_H_INCLUDED
#define BMP_H_INCLUDED
#include "stdio.h"
#include "Mat.h"


 int    (*filewrite)(const void *  _Str,int _Size,int _Count,FILE *  _File);
 int    (*fileread)(void * _DstBuf,int _ElementSize,int _Count,FILE * _File);
 FILE * (*fileopen)(const char *  _Filename,const char *  _Mode) ;
 int    (*fileseek)(FILE *_File,long _Offset,int _Origin);
 int    (*fileclose)(FILE *_File);
 void   (*Li_free)(void *_Memory);
 void * (*Li_malloc)(size_t _Size);
 void * (*Li_memcpy)(void * _Dst,const void * _Src,size_t _Size);
 void   (*show)(Mat* mat);
 u8*    (*at)(Mat* mat,int width,int highth);
 int    (*process)(Mat* mat,int x,int y,u32 color);
 Mat    (*load)(char *filepath);
 int    (*save)(char *filepath,Mat* mat);
 Mat    (*copy)(Mat mat);
 void   (*destory)(Mat* mat);

//检查路径是否合法：文件能打开；以bmp为后缀名
int CheckbmpFilePath(char *filepath);
//读入位图的文件头
int ReadbmpFileHeader(char *filepath,BITMAPFILEHEADER *bmfh);
//打印位图的文件头
void PrintbmpFileHeader(BITMAPFILEHEADER *bmfh);
//读入位图的信息头
int ReadbmpInfoHeader(char *filepath,BITMAPINFOHEADER *bmih);
//打印位图的信息头
void PrintbmpInfoHeader(BITMAPINFOHEADER *bmih);
//读入位图的像素数据
int ReadbmpPixelData(char *filepath,BYTE *imgData);
//计算每行像素所占的字节数
LONG GetLineBytes(int imgWidth,int bitCount);
//打印位图的像素数据
void PrintbmpPixelData(BYTE *imgData,int width,int height,int bitCount);
//另存为位图
int SaveAsbmpImage(char *filepath,Mat* mat);
//显示位图
void ShowbmpImage(Mat* mat);
//bmp文件的读取与解码函数
Mat bmpload(char *filepath);
//BMP图片处理单个像素点
int bmpprocess(Mat* mat,int width,int highth,u32 color);
//BMP像素点寻址函数
u8* bmpat(Mat* mat,int width,int highth);

Mat bmpcopy(Mat mat);

void bmpdestory(Mat* mat);

#endif // BMP_H_INCLUDED







