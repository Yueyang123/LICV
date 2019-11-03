/*************************************************
Copyright © Yueyang Co. Ltd. 2019-2029. All rights reserved.
File name: remap.h
Author： Yueyang
Version: V1.0
Description: 提供图像的展开算法
Others: 
Log: 11.3 Yueyang
*************************************************/
#ifndef REMAP_H
#define REMAP_H

#include "cv.h"
#include "bmp.h"

Mat creatMapMat(Mat src, 
                 int rows_c,
                 int cols_c);

#endif