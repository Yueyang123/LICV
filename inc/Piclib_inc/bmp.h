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
int SaveAsbmp24Image(char *filepath,Mat* mat);

//加载BMP图片，并返回一个MAT结构体
Mat bmpload(char* dstname,char *filepath);


#endif 







