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
#include "PointOr.h"
#include "BasicGui.h"

int main()
{
     Mat src;
     Mat_Init();
     src=load("..\\picture\\hole.bmp");

     Mat dst=dst=creatMapMat(src, 500,500,PI/4);

     save("..\\picture\\test.bmp",&dst);

     show(&dst);

    //   destory(&src);
     destory(&dst);
      return 0; 
}

 