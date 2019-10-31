#ifndef BMP_H_INCLUDED
#define BMP_H_INCLUDED

#include "cv.h"
#include "Mat.h"


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


#endif // BMP_H_INCLUDED







