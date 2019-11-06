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
#include "remap.h"

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
    printf("1");
    dst=create("..\\picture\\test.bmp",cols_c,rows_c,3);
	double delta_r = polar_r / rows_c; //半径因子
	double delta_t = 2.0*PI / cols_c;  //角度因子
	double center_polar_x = (polar_d - 1) / 2.0;
	double center_polar_y = (polar_d - 1) / 2.0;
    printf("2");
    for (i = 0; i < cols_c; i++)
	{
		double theta_p = i * delta_t; //方图第i列在圆图对应线的角度
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

int main()
{
     Mat src;
     Mat_Init();
       src=load("..\\picture\\hole.bmp");
    // src=load("..\\picture\\hole.bmp");
   //  save("..\\picture\\test.bmp",&src);
   //  PrintbmpFileHeader(&src.bmf);
   //  PrintbmpInfoHeader(&src.bmi);
   // show(&dst);
   // destory(&dst);
   // destory(&src);
     Mat dst= creatMapMat(src,1000,1000);
     save("..\\picture\\test.bmp",&dst);
     destory(&src);
     destory(&dst);

//printf("%d,%d,%d,%d",sizeof(BYTE),sizeof(WORD),sizeof(DWORD),sizeof(LONG));
   return 0; 
}

 