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
#include <math.h>

#define PI   3.1415


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
    double angle;
    int step = 0;
	int Rot_step = 0;
    int i, j;
    int midX_pre,midY_pre,midX_aft,midY_aft;
    int pre_i,pre_j,after_i,after_j;
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




/**
 * @fn  float fastSin(float x)
 *
 * @brief   自定义快速变换 sin  cos  函数  定义 而外精度 更高拟合效果 参考链接
 *          https://www.cnblogs.com/sun11086/archive/2009/03/20/1417944.html
 *
 * @author  IRIS_Chen
 * @date    2019/6/17
 *
 * @param   x   The x coordinate
 *
 * @return  A float
 */
//本质上是利用了一个已经拟合好的二次函数近似三角函数
float fastSin(float x)
{
    float y;
    // 限定 x 在 -Pi  到 pi
    while (x < - PI)
    {
        x += (float)(2 * PI);
    }
    while (x > PI)
    {
        x -= (float)(2 * PI);
    }

    const float B = 1.2732; // 4 / CV_PI;
    const float C = -0.4053; // -4 / (CV_PI*CV_PI);
    if(x>0)
    {
    y = B * x + C * x * x;
    }
    else
    {
     y = -1*B * x + C * x * x;
    }
    return y;
}


/**
 * @fn  float fastCos(float x)
 *
 * @brief   Fast cosine
 *
 * @author  IRIS_Chen
 * @date    2019/6/17
 *
 * @param   x   The x coordinate
 *
 * @return  A float
 */
float fastCos(float x)
{
    return fastSin(x + 1.5707);
}


Mat creatMapMat(Mat src, 
                 int rows_c,
                 int cols_c)
{
    Mat dst;
    int i,j;
    u8* inaddr;
    u8* outaddr;
    int polar_d =src.width;
    double polar_r = polar_d / 2.0;
    dst=copy(src);
	double delta_r = polar_r / rows_c; //半径因子
	double delta_t = 2.0*PI / cols_c;  //角度因子
	double center_polar_x = (polar_d - 1) / 2.0;
	double center_polar_y = (polar_d - 1) / 2.0;

    for (i = 0; i < cols_c; i++)
	{
		double theta_p = i * delta_t; //方图第i列在圆图对应线的角度
		double sin_theta = fastSin(theta_p);
		double cos_theta = fastCos(theta_p);
 
		for (int j = 0; j < rows_c; j++)
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
