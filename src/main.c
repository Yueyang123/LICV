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
#include "Piclib.h"

int main()
{
     Mat dst;
     Mat_Init;
     u8* inaddr;
     int x,y;
     Mat src1 = readpng("..\\picture\\test.bmp","..\\picture\\lena.png");
     Mat src2 = read_JPEG_file("..\\picture\\test1.bmp","..\\picture\\lena.jpg");
     save("..\\picture\\test.bmp",&src1);
     save("..\\picture\\test1.bmp",&src2);
     show(&src1);
     show(&src2);
     return 0; 
}

 