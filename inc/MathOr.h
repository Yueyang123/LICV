/*************************************************
Copyright © Yueyang Co. Ltd. 2019-2029. All rights reserved.
File name:PointOr.c
Author： Yueyang
Version: V1.0
Description: 提供对于图片算数运算
Others: 
Log: 11.14 Yueyang
*************************************************/
#ifndef MATHOR_H
#define MATHOR_H

#include "Mat.h"


Mat Matplus(Mat src1,Mat src2,int x,int y);

Mat Matmean(Mat src1,Mat src2,int x,int y);

Mat Matdivide(Mat src1,Mat src2,int x,int y);

Mat Matmultiply(Mat src1,Mat src2,int x,int y);

Mat Matminus(Mat src1,Mat src2,int x,int y);

#endif // !MATHOR_H

