#ifndef BASIC_H
#define BASIC_H

#include "cv.h"
#include "bmp.h"

void DrawPoint(Mat* mat,u32 color,int x,int y);
void DrawLine(Mat* mat,u32 color,u16 x1, u16 y1, u16 x2, u16 y2);
void ShowString(Mat* mat,u32 color,u8*p,u16 x,u16 y,u16 width,u16 height,u8 size);
void DrawCircle(Mat* mat ,u32 color,u16 x0,u16 y0,u8 r);
Mat DrawCDF(float* result,u32 length,u32 cols,u32 rows);
#endif