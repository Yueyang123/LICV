/*************************************************
Copyright © Yueyang Co. Ltd. 2019-2029. All rights reserved.
File name: GeoTrans.c
Author： Yueyang
Version: V1.0
Description: 提供对于图片的几何变换
Others: 
Log: 11.3 Yueyang
*************************************************/

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


/**
 * @fn      Mat imrotate(Mat mat,int Angle)
 *
 * @brief   逆时针旋转一个固定的角度
 *          Angle (0-360)
 *
 * @author  Yueyang
 * @date    2019/11/13
 *
 * @param   mat   The picture type
 *          Angle the angle you need you rotate(0-360)
 * 
 * @return  A picture type
 */
Mat imrotate(Mat mat,int Angle)
{
    u8* inaddr;
    u8* outaddr;
    double angle;
    int i, j;
    int pre_i,pre_j,after_i,after_j;
    angle = 1.0 * Angle * PI / 180;
    Mat out=copy(&mat);

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
    
		for(i = 0;i < mat.highth;i++)
		{
			for(j = 0;j < mat.width;j++)
			{
				after_i = i;
				after_j = j;
				pre_i = (int)(cos((double)angle) * after_i - sin((double)angle) * after_j) + mat.width/2-60;
				pre_j = (int)(sin((double)angle) * after_i + cos((double)angle) * after_j)-80;

                inaddr=at(&out,after_i,after_j);
                outaddr=at(&mat,pre_i,pre_j);
                if(pre_i<mat.width&&pre_j<mat.highth&&pre_j>=0&&pre_i>=0)
                 PointSwap(inaddr,outaddr);
			}
		}
        return out;
} 

/**
 * @fn      Mat immove(Mat mat,int dir,int distance)
 *
 * @brief   向指定方向移动图片（图片保持原大小）
 *          超出图片原本大小的部分将被舍去
 *
 * @author  Yueyang
 * @date    2019/11/13
 *
 * @param   mat      The picture type
 *          dir      The direction you want to move
 *          distance (pix)是像素值
 * 
 * @return  A picture type
 */
Mat immove(Mat mat,int dir,int distance)
{
    u8* inaddr;
    u8* outaddr;
    Mat out=copy(&mat);
    int i,j;

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

/**
 * @fn      Mat creatMapMat(Mat src, 
                            int rows_c,
                            int cols_c,
                            double startdelta)
 *
 * @brief   鱼眼图展开算法
 *
 * @author  Yueyang
 * @date    2019/11/13
 *
 * @param   src         The picture type
 *          rows_c      图像的高度对应y
 *          cols_c      图像的宽度对应x
 *          startdelta  图像展开的其实坐标（0-2PI）
 * @return  A picture type
 */
Mat creatMapMat(Mat src, 
                 int rows_c,
                 int cols_c,
                 double startdelta)
{
    Mat dst;
    u8* inaddr;
    u8* outaddr;
    int i,j;
    int polar_d =src.width;
    double polar_r = polar_d / 2.0;
    dst=Create("..\\picture\\test.bmp",cols_c,rows_c,3);
	double delta_r = polar_r / rows_c; //半径因子
	double delta_t = 2.0*PI / cols_c;  //角度因子
	double center_polar_x = (polar_d - 1) / 2.0;
	double center_polar_y = (polar_d - 1) / 2.0;
    printf("2");
    for (i = 0; i < cols_c; i++)
	{
		double theta_p = i * delta_t+startdelta; //方图第i列在圆图对应线的角度
		double sin_theta = sin(theta_p);
		double cos_theta = cos(theta_p);
 
        for (j = 0; j < rows_c; j++)
		{
			double temp_r = j * delta_r; //方图第j行在圆图上对应的半径长度
 
			int polar_x = (int)(center_polar_x + temp_r * cos_theta);
			int polar_y = (int)(center_polar_y - temp_r * sin_theta);
            if(i<dst.width&&j<dst.highth&&polar_x<src.width&&polar_y<=src.highth)
            {
            inaddr=at(&dst,i,j);
            outaddr=at(&src,polar_x,polar_y);
            *inaddr=*outaddr;
            *(inaddr+1)=*(outaddr+1);
            *(inaddr+2)=*(outaddr+2);
            }
		}
	}
    return dst;
}
