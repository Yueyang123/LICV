#ifndef POINTOR_H
#define POINTOR_H

#include "cv.h"
#include "bmp.h"

Mat GetBW(Mat src);
Mat GetGray(Mat src,u8* buf);//注意必须放入的是一个已经申请过的内存块
float* CDFProcess(u8* buf,int length);
Mat EqualizeHistogram(Mat src);

#endif // !POINTOR_H


