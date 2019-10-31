/*
*版权所有 (C)2019,Yueyang.
*文件名称：Mat.h
*内容摘要：LiteCV基础数据类型Mat实现
*当前版本：V1.0
*作者：杨越
*完成日期：20191020
*/

#ifndef Mat_H
#define MAT_H

#include "cv.h"



#define BMP_8    0X01
#define BMP_565  0x02
#define BMP_888  0x03
#define BMP_32   0x04
#define JPEG     0X05

#define     RGB(r,g,b)     ((u32)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16))) 



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




typedef struct
{
    //! the number of rows and columns or (-1, -1) when the matrix has more than 2 dimensions

     BITMAPFILEHEADER bmf;
     BITMAPINFOHEADER bmi;

    LONG highth, width;
    u8 pictype;
    char* PATH;
    BYTE *imgData;

}Mat;

void Mat_INIT();

#endif // !Mat_H
