/*************************************************
Copyright © Yueyang Co. Ltd. 2019-2029. All rights reserved.
File name: cv.h
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
#include "GeoTrans.h"

int main()
{
   Mat src;
   Mat dst;
   int i,j;
   Mat_INIT();
   src=load("..\\picture\\lena0.bmp");

   dst=imrotate(src,30);
   save("..\\picture\\lena.bmp",&dst);
   show(&dst);
   destory(&dst);
   destory(&src);
   return 0; 
}

 