/*************************************************
Copyright © Yueyang Co. Ltd. 2019-2029. All rights reserved.
File name:PointOr.c
Author： Yueyang
Version: V1.0
Description: 提供图片的颜色识别算法
Others: 
Log: 11.13 Yueyang
*************************************************/

#include "RGB2HSL.h"
#include "cv.h"

//图像检测的相关阈值
#define R_H     30    
#define G_H     100
#define B_H     140

//可见的饱和度范围
#define SL      80
#define SH      240
//颜色可见的亮度范围
#define LL      80
#define LH      200

#define RED    1
#define BLUE   2
#define GREEN  3
#define BLACKorWHITE  4


/**
 * @fn      u8 PointColorDec(u8 R,u8 G,u8 B)
 *
 * @brief   点的颜色检测，返回红绿蓝中的一种
 *
 * @author  Yueyang
 * @date    2019/11/15
 *
 * @param  R,G,B
 * 
 * @return color type
 */
u8 PointColorDec(u8 R,u8 G,u8 B)
{
    double h,s,l;
    RGB2HLS(&h,&l,&s,R,G,B);


            if ((u8)h<170&&(u8)h>160)
            {
            return RED;
            }
            else if (h<160&&h>35)
            {
            return GREEN;
            }
            else if (h<255&&h>220)
            {
            return BLUE;
            }

}


/**
 * @fn      Mat ColorDec(Mat src)
 *
 * @brief   返回一张颜色检测的图片
 *
 * @author  Yueyang
 * @date    2019/11/16
 *
 * @param  src a picture
 * 
 * @return a picture
 */
Mat ColorDec(Mat src)
{
    int x,y;
    u8* inaddr,*outaddr;
    u8 temp;
    Mat dst=copy(&src);
    for(y=0;y<src.width;y++)
    for(x=0;x<src.highth;x++)
    {
         inaddr=at(&src,x,y);
         outaddr=at(&dst,x,y);
         temp=PointColorDec(*(inaddr+2),*(inaddr+1),*(inaddr));
        if(temp==RED)
        {
            *(outaddr)=0x00;
            *(outaddr+1)=0x00;
            *(outaddr+2)=0xFF;
        }
         else if(temp==GREEN)
        {
            *(outaddr)=0x00;
            *(outaddr+1)=0xFF;
            *(outaddr+2)=0x00;
        }
         else if(temp==BLUE)
        {
            *(outaddr)=0xFF;
            *(outaddr+1)=0x00;
            *(outaddr+2)=0x00;
        }
        else
        {
            *(outaddr)=0x00;
            *(outaddr+1)=0x00;
            *(outaddr+2)=0x00;
        }
        

    }
    return dst;

}






