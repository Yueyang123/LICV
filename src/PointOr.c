/*************************************************
Copyright © Yueyang Co. Ltd. 2019-2029. All rights reserved.
File name:PointOr.c
Author： Yueyang
Version: V1.0
Description: 提供对于图片点运算
Others: 
Log: 11.8 Yueyang
*************************************************/

#include "PointOr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define GATE    8388608

//返回一个24位的灰度图,同时返回一个包涵灰度值的数组
//对于灰度值的计算这里采用均值算法
Mat GetGray(Mat src,u8* buf)
{
 u32 x,y;
 u8* inaddr;
 u8* outaddr;
 u32 color,GRAY;
 Mat dst=copy(src);

 for(x=0;x<src.width;x++)
 for(y=0;y<src.highth;y++)
 {
     inaddr=at(&dst,x,y);
     outaddr=at(&src,x,y);
     GRAY=(*(outaddr)+*(outaddr+1)+*(outaddr+2))/3;
     *(buf+x*src.width+y)=GRAY;
        *inaddr=GRAY;
        *(inaddr+1)=GRAY;
        *(inaddr+2)=GRAY;
 }
 return dst;
}

Mat GetBW(Mat src)
{
 u32 x,y;
 u8* inaddr;
 u8* outaddr;
 u32 color;
 Mat dst=copy(src);
 for(x=0;x<src.width;x++)
 for(y=0;y<src.highth;y++)
 {
     inaddr=at(&dst,x,y);
     outaddr=at(&src,x,y);
     color=(u32)RGB(*(outaddr+2),*(outaddr+1),*(outaddr));
     if (color>GATE)
     {
        *inaddr=0xFF;
        *(inaddr+1)=0xFF;
        *(inaddr+2)=0xFF;
     }
     else
     {
        *inaddr=0X00;
        *(inaddr+1)=0X00;
        *(inaddr+2)=0X00;
     }
    
 }
  return dst;
}

//灰度值的显示函数概率显示
void ShowCDF(float* CDF)
{
   int i;
   for(i=0;i<256;i++)
   {
      printf(" CDF[%d] =%f\n",i,CDF[i]);
   }

}

//提供对于灰度值的直方图统计
//返回一个浮点数组概率向量
float* CDFProcess(u8* buf,int length)
{
   u32 i=0;
   float* buffer;//存储0-255的数值出现的次数
   float* result;
   //将申请的地址全部初始化为0
   buffer=malloc(256*sizeof(float));
   result=malloc(256*sizeof(float));
   memset(buffer,0,256*4);
   memset(result,0,256*4);

   for(i=0;i<length;i++)
   {
      buffer[(u8)(*(buf+i))]++;
   }

   for(i=0;i<256;i++)
   {
      result[i]=buffer[i]/length;
   }

   ShowCDF(result);

   return result;
}

