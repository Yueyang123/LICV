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
     Mat src,dst,CDF;
     Mat_Init();
     u8* inaddr;
     int x,y;
     src=load("..\\picture\\WHU1.bmp");
      u8* buf=malloc(src.width*src.highth*sizeof(BYTE));  
      dst=MatReshape(src,500,500);
      dst=EqualizeHistogram(dst);

      save("..\\picture\\test1.bmp",&dst);
      show(&dst);
      GetGray(dst,buf);
      float* data=CDFProcess(buf,dst.width*dst.highth);
      CDF=DrawCDF(data,240,500,500);
      save("..\\picture\\CDF2.bmp",&CDF);
      show(&CDF);

      return 0; 
}

 