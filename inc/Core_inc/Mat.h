/*************************************************
Copyright © Yueyang Co. Ltd. 2019-2029. All rights reserved.
File name: Mat.h
Author： Yueyang
Version: V1.0
Description: 提供Mat结构体
Others: 
Log: 11.3 Yueyang
*************************************************/

#ifndef Mat_H
#define Mat_H

#include "cv.h"


#define BMP_8    0X01
#define BMP_565  0x02
#define BMP_888  0x03
#define BMP_32   0x04
#define JPEG     0X05

#define     RGB(r,g,b)     ((u32)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16))) 

#ifdef __cplusplus
extern "C" {
#endif

typedef struct 
{ // bmfh
    WORD    bfType;
    DWORD   bfSize;
    WORD    bfReserved1;
    WORD    bfReserved2;
    DWORD   bfOffBits;
}BITMAPFILEHEADER;
typedef struct 
{ // bmih
    DWORD biSize;
    LONG   biWidth;
    LONG   biHeight;
    WORD   biPlanes;
    WORD   biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    LONG   biXPelsPerMeter;
    LONG   biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;
}BITMAPINFOHEADER;
typedef struct tagRGBQUAD
{ // rgbq
    BYTE    rgbBlue;
    BYTE    rgbGreen;
    BYTE    rgbRed;
    BYTE    rgbReserved;
}RGBQUAD;

typedef struct tagBITMAPINFO
{
    BITMAPINFOHEADER bmiHeader;
    RGBQUAD bmiColors[1];
}BITMAPINFO;


//以BMP为基础的图片数据类型
//读取其他中类的图片需要先将其转化
typedef struct
{
    BITMAPFILEHEADER bmf;
    BITMAPINFOHEADER bmi;

    LONG highth, width;
    u8 pictype;
    char* PATH;
    BYTE *imgData;

}Mat;

typedef struct tagPOINT
{
    u32 x;
    u32 y;
}POINT;

static inline POINT GetPoint(u32 a,u32 b) 
{
    POINT p;
     p.x=a;
     p.y=b;
     return p;
}
#ifdef __cplusplus
}
#endif

//对于图片的每一个像素分别操作
int Matchange(Mat* mat,int width,int highth,u32 color);
//获取某个像素所在的地址
u8* Matat(Mat* mat,int width,int highth);
//BMP拷贝函数
Mat Matcopy(Mat* mat);
//析构函数
void Matdestory(Mat* mat);
//矩阵类创建函数
Mat MatCreate(u8* filepath,u16 width,u16 height,u8 type);
//图像类重新调整大小的函数
Mat MatReshape(Mat src,u32 cols_c,int rows_c);
//图片显示 注意在不同的硬件平台上需要重写这个函数
void ShowImage(Mat* mat,char* winname);
Mat Matload(char* dstname ,char * filename);
//通配指针提供，跨平台主要的实现方式
 void   (*Show)      (Mat* mat,char* winname);
 u8*    (*at)        (Mat* mat,int width,int highth);
 int    (*change)    (Mat* mat,int x,int y,u32 color);
 Mat    (*Load)      (char* dstname ,char * filename);
 int    (*save)      (char *filepath,Mat* mat);
 Mat    (*Copy)      (Mat* mat);
 void   (*destory)   (Mat* mat);
 Mat    (*Create)    (u8* filepath,u16 width,u16 height,u8 type);
 Mat    (*reshape)   (Mat src,u32 cols_c,int rows_c);


//对于常见函数进行指针赋值
#define Mat_Init   \
        Show=ShowImage;\
        at=Matat;\
        change=Matchange;\
        Load=Matload;\
        save=SaveAsbmp24Image;\
        destory=Matdestory;\
        Copy=Matcopy;\
        Create=MatCreate;\
        reshape=MatReshape




#endif // !Mat_H
