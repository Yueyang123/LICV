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


int main()
{
     Mat src1,src2,dst;
     Mat_Init;
     u8* inaddr;
     int x,y;
     src1=load("..\\picture\\lena8.bmp");
//      src2=load("..\\picture\\lena.bmp");
//      src1=reshape(src1,1000,1000);
//      src2=reshape(src2,1000,1000);
//      dst=Matmean(src1,src2,0,0);
     save("..\\picture\\test.bmp",&src1);
     show(&src1);
      return 0; 
}

 