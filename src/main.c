/*************************************************
Copyright © Yueyang Co. Ltd. 2019-2029. All rights reserved.
File name: main.c
Author： Yueyang
Version: V1.0
Description: LiteCV运行主函数
Others: 
Log: 11.3 Yueyang
*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "bmp.h"
#include "cv.h"
#include "Mat.h"
#include "GeoTrans.h"
#include "PointOr.h"
#include "MathOr.h"
#include "BasicGui.h"
#include "RGB2HSL.h"
#include "ColorDec.h"


int main()
{
     Mat src1,src2,dst;
     Mat_Init;
     u8* inaddr;
     int x,y;
     src1=load("..\\picture\\lena8.bmp");
     save("..\\picture\\test.bmp",&src1);
     show(&src1);
     return 0; 
}

 