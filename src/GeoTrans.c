/*
*版权所有 (C)2019,Yueyang.
*文件名称：main.c
*内容摘要：LiteCV几何变换
*当前版本：V1.0
*作者：杨越
*完成日期：20191020
*/

#include "cv.h"
#include "bmp.h"
#include "GeoTrans.h"
#include <math.h>
#include <stdio.h>

void PointSwap(u8* inaddr,u8* outaddr)
{
    *inaddr=*outaddr;
    *(inaddr+1)=*(outaddr+1);
    *(inaddr+2)=*(outaddr+2);
}


Mat imrotate(Mat mat,int Angle)
{
    u8* inaddr;
    u8* outaddr;
    double angle;//要旋转的弧度数
    int step = 0;
	int Rot_step = 0;
    int i, j;
    int midX_pre,midY_pre,midX_aft,midY_aft;//旋转前后的中心点的坐标
    int pre_i,pre_j,after_i,after_j;//旋转前后对应的像素点坐标
    angle = 1.0 * Angle * PI / 180;
    Mat out=copy(mat);

        for ( i = 0; i < mat.width; i++)
        {
            for ( j = 0; j < mat.highth; j++)
            {
                 inaddr=at(&out,i,j);
                *inaddr=0x00;
                *(inaddr+1)=0x00;
                *(inaddr+2)=0x00;
            }
        }
        //坐标变换
		for(i = 0;i < mat.highth;i++)
		{
			for(j = 0;j < mat.width;j++)
			{
				after_i = i;
				after_j = j;
				pre_i = (int)(cos((double)angle) * after_i - sin((double)angle) * after_j) + mat.width/2-90;
				pre_j = (int)(sin((double)angle) * after_i + cos((double)angle) * after_j)-30;

                inaddr=at(&out,after_i,after_j);
                outaddr=at(&mat,pre_i,pre_j);
                if(pre_i<mat.width&&pre_j<mat.highth&&pre_j>=0&&pre_i>=0)
                 PointSwap(inaddr,outaddr);
			}
		}
        return out;
} 

//DIR:0左  1右 2上  3 下
//distance 移动的像素距离
Mat immove(Mat mat,int dir,int distance)
{
    u8* inaddr;
    u8* outaddr;
    Mat out=copy(mat);
    int i,j,x,y;

        for ( i = 0; i < mat.width; i++)
        {
            for ( j = 0; j < mat.highth; j++)
            {
                 inaddr=at(&out,i,j);
                *inaddr=0x00;
                *(inaddr+1)=0x00;
                *(inaddr+2)=0x00;
            }
        }


        switch (dir)
        {
        case 1:
                for ( i = distance; i < mat.width; i++)
                {
                    for ( j = 0; j < mat.highth; j++)
                    {
                        inaddr=at(&out,i-distance,j);
                        outaddr=at(&mat,i,j);
                        PointSwap(inaddr,outaddr);
                        
                    }
                }
            break;
        
        case 0:
                for ( i = 0; i < mat.width-distance; i++)
                {
                    for ( j = 0; j < mat.highth; j++)
                    {
                        inaddr=at(&out,i+distance,j);
                        outaddr=at(&mat,i,j);
                        PointSwap(inaddr,outaddr);
                    }
                }
            break;

        case 3:
                for ( i = 0; i < mat.width; i++)
                {
                    for ( j = distance; j < mat.highth; j++)
                    {
                        inaddr=at(&out,i,j);
                        outaddr=at(&mat,i,j-distance);
                        PointSwap(inaddr,outaddr);
                        
                    }
                }
            break;

        case 2:
                for ( i = 0; i < mat.width; i++)
                {
                    for ( j = 0; j < mat.highth-distance; j++)
                    {
                        inaddr=at(&out,i,j);
                        outaddr=at(&mat,i,j+distance);
                        PointSwap(inaddr,outaddr);
                        
                    }
                }
            break;

        default:
            break;
        }



    return out;

}