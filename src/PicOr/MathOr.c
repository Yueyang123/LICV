/*************************************************
Copyright © Yueyang Co. Ltd. 2019-2029. All rights reserved.
File name:PointOr.c
Author： Yueyang
Version: V1.0
Description: 提供对于图片算数运算
Others: 
Log: 11.13 Yueyang
*************************************************/
#include "MathOr.h"
#include "cv.h"


static inline u32 plus(u8* inaddr,u8* outaddr)
{
return RGB(*(inaddr+2),*(inaddr+1),*(inaddr))+RGB(*(outaddr+2),*(outaddr+1),*(outaddr));
}

static inline u32 mean(u8* inaddr,u8* outaddr)
{
return (RGB(*(inaddr+2),*(inaddr+1),*(inaddr))+RGB(*(outaddr+2),*(outaddr+1),*(outaddr)))/2;
}

static inline u32 minus(u8* inaddr,u8* outaddr)
{
return RGB(*(inaddr+2),*(inaddr+1),*(inaddr))-RGB(*(outaddr+2),*(outaddr+1),*(outaddr));
}

static inline u32 mulitiply(u8* inaddr,u8* outaddr)
{
return RGB(*(inaddr+2),*(inaddr+1),*(inaddr))*RGB(*(outaddr+2),*(outaddr+1),*(outaddr));
}

static inline u32 divide(u8* inaddr,u8* outaddr)
{
return RGB(*(inaddr+2),*(inaddr+1),*(inaddr))/RGB(*(outaddr+2),*(outaddr+1),*(outaddr));
}

/**
 * @fn      Mat Matplus(Mat src1,Mat src2,int x,int y)
 *
 * @brief   将两个图像简单相加
 *          第一张作为背景图
 *
 * @author  Yueyang
 * @date    2019/11/14
 *
 * @param   src1   The picture type as the background
 *          src2   The picture type on the background
 *          x,y    第二张图片相对于第一张图片的位置 
 * 
 * @return  A picture type
 */
Mat Matplus(Mat src1,Mat src2,int x,int y)
{
    int i,j;
    u8* inaddr;
    u8 *addr1,*addr2;
    u32 temp;
    Mat dst= copy(&src1);
    for(i=x;i<dst.width;i++)
    for(j=y;j<dst.highth;j++)
    {
        if(i-x<src2.width&&j-y<src2.highth)
        {
        addr1=at(&src1,i,j);
        addr2=at(&src2,i-x,j-y);
        temp=plus(addr1,addr2);
        inaddr=at(&dst,i,j);
        *inaddr=(u8)((temp&0x00FF0000)>>16);//B
        *(inaddr+1)=(u8)((temp&0x0000FF00)>>8);//G
        *(inaddr+2)=(u8)(temp&0x000000FF);//R
        }
    }
    return dst;
}


/**
 * @fn      Mat Matmean(Mat src1,Mat src2,int x,int y)
 *
 * @brief   将两个图像简单相加后取平均，可用于多张角度相同的图片
 *          消除噪声
 *          第一张作为背景图
 *
 * @author  Yueyang
 * @date    2019/11/14
 *
 * @param   src1   The picture type as the background
 *          src2   The picture type on the background
 *          x,y    第二张图片相对于第一张图片的位置 
 * 
 * @return  A picture type
 */
Mat Matmean(Mat src1,Mat src2,int x,int y)
{
    int i,j;
    u8* inaddr;
    u8 *addr1,*addr2;
    u32 temp;
    Mat dst= copy(&src1);
    for(i=x;i<dst.width;i++)
    for(j=y;j<dst.highth;j++)
    {
        if(i-x<src2.width&&j-y<src2.highth)
        {
        addr1=at(&src1,i,j);
        addr2=at(&src2,i-x,j-y);
        temp=mean(addr1,addr2);
        inaddr=at(&dst,i,j);
        *inaddr=(u8)((temp&0x00FF0000)>>16);//B
        *(inaddr+1)=(u8)((temp&0x0000FF00)>>8);//G
        *(inaddr+2)=(u8)(temp&0x000000FF);//R
        }
    }
    return dst;
}



/**
 * @fn      Mat Matminus(Mat src1,Mat src2,int x,int y)
 *
 * @brief   将两个图像简单相减
 *          插影法消除背景对于主要部分的影响
 *          还可以通过两个不同时刻的照片进行比对分析
 * @author  Yueyang
 * @date    2019/11/14
 *
 * @param   src1   The picture type as the background
 *          src2   The picture type on the background
 *          x,y    第二张图片相对于第一张图片的位置 
 * 
 * @return  A picture type
 */
Mat Matminus(Mat src1,Mat src2,int x,int y)
{
    int i,j;
    u8* inaddr;
    u8 *addr1,*addr2;
    u32 temp;
    Mat dst= copy(&src1);
    for(i=x;i<dst.width;i++)
    for(j=y;j<dst.highth;j++)
    {
        if(i-x<src2.width&&j-y<src2.highth)
        {
        addr1=at(&src1,i,j);
        addr2=at(&src2,i-x,j-y);
        temp=minus(addr1,addr2);
        inaddr=at(&dst,i,j);
        *inaddr=(u8)((temp&0x00FF0000)>>16);//B
        *(inaddr+1)=(u8)((temp&0x0000FF00)>>8);//G
        *(inaddr+2)=(u8)(temp&0x000000FF);//R
        }
    }
    return dst;
}



/**
 * @fn      Mat Matmultiply(Mat src1,Mat src2,int x,int y)
 *
 * @brief   将两个图像简单相乘
 *          可用作于掩模图像相乘除去背景
 *          一般情况下掩模图像需要人工绘之
 * @author  Yueyang
 * @date    2019/11/14
 *
 * @param   src1   The picture type as the background
 *          src2   The picture type on the background
 *          x,y    第二张图片相对于第一张图片的位置 
 * 
 * @return  A picture type
 */
Mat Matmultiply(Mat src1,Mat src2,int x,int y)
{
    int i,j;
    u8* inaddr;
    u8 *addr1,*addr2;
    u32 temp;
    Mat dst= copy(&src1);
    for(i=x;i<dst.width;i++)
    for(j=y;j<dst.highth;j++)
    {
        if(i-x<src2.width&&j-y<src2.highth)
        {
        addr1=at(&src1,i,j);
        addr2=at(&src2,i-x,j-y);
        temp=mulitiply(addr1,addr2);
        inaddr=at(&dst,i,j);
        *inaddr=(u8)((temp&0x00FF0000)>>16);//B
        *(inaddr+1)=(u8)((temp&0x0000FF00)>>8);//G
        *(inaddr+2)=(u8)(temp&0x000000FF);//R
        }
    }
    return dst;
}



/**
 * @fn      Mat Matdivide(Mat src1,Mat src2,int x,int y)
 *
 * @brief   将两个图像简单相除
 *          不知道有什么用
 * @author  Yueyang
 * @date    2019/11/14
 *
 * @param   src1   The picture type as the background
 *          src2   The picture type on the background
 *          x,y    第二张图片相对于第一张图片的位置 
 * 
 * @return  A picture type
 */
Mat Matdivide(Mat src1,Mat src2,int x,int y)
{
    int i,j;
    u8* inaddr;
    u8 *addr1,*addr2;
    u32 temp;
    Mat dst= copy(&src1);
    for(i=x;i<dst.width;i++)
    for(j=y;j<dst.highth;j++)
    {
        if(i-x<src2.width&&j-y<src2.highth)
        {
        addr1=at(&src1,i,j);
        addr2=at(&src2,i-x,j-y);
        temp=divide(addr1,addr2);
        inaddr=at(&dst,i,j);
        *inaddr=(u8)((temp&0x00FF0000)>>16);//B
        *(inaddr+1)=(u8)((temp&0x0000FF00)>>8);//G
        *(inaddr+2)=(u8)(temp&0x000000FF);//R
        }
    }
    return dst;
}