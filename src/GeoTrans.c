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
				pre_i = (int)(cos((double)angle) * after_i - sin((double)angle) * after_j) + mat.width/2-20;
				pre_j = (int)(sin((double)angle) * after_i + cos((double)angle) * after_j)-120;

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


Mat creatMapMat(Mat src, 
                 int rows_c,
                 int cols_c,
                 double startdelta)
{
    Mat dst;
    int i,j;
    u8* inaddr;
    u8* outaddr;
    int polar_d =src.width;
    double polar_r = polar_d / 2.0;
    printf("1");
    dst=create("..\\picture\\test.bmp",cols_c,rows_c,3);
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


//cols横向 ，rows纵向
Mat MatReshape(Mat src,u32 cols_c,int rows_c)
{
   Mat dst;
   u32 x,y;
   u8* inaddr;
   u8* outaddr;
   double x_fact=(double)cols_c/src.width;
   double y_fact=(double)rows_c/src.highth;

   printf("(xfact,yfact)=(%f,%f)",x_fact,y_fact);

   dst=create("..\\picture\\test.bmp",cols_c,rows_c,3);

    for(x=0;x<cols_c;x++)
    for(y=0;y<rows_c;y++)
    {
      inaddr=at(&dst,x,y);
      outaddr=at(&src,(int)x/x_fact,(int)y/y_fact);
      PointSwap(inaddr,outaddr);
    }
    return dst;

}
