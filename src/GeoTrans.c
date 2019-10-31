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

Mat imrotate(Mat bmpImg,int Angle)
{
    double angle;//要旋转的弧度数
    int width = 0;
    int highth = 0;
    int step = 0;
	int Rot_step = 0;
	int channels = 3;
    int i, j, k;
    u8* addr;
	width = bmpImg.width;
	highth = bmpImg.highth;
    int midX_pre,midY_pre,midX_aft,midY_aft;//旋转前后的中心点的坐标
    midX_pre = width / 2;
    midY_pre = highth / 2;
    int pre_i,pre_j,after_i,after_j;//旋转前后对应的像素点坐标
    angle = 1.0 * Angle * PI / 180;
    Mat out=copy(bmpImg);
	step = channels * width;
	Rot_step = channels * bmpImg.width;
		
        for ( i = 0; i < out.highth; i++)
        {
            for ( j = 0; j < out.width; j++)
            {
                addr=at(&out,i,j);
                *addr=0x00;
                *(addr+1)=0x00;
                *(addr+2)=0x00;
            }
            
        }
        
        
        
        //坐标变换
		for(i = 0;i < bmpImg.highth;i++)
		{
			for(j = 0;j < bmpImg.width;j++)
			{
				after_i = i - midX_aft;
				after_j = j - midY_aft;
				pre_i = (int)(cos((double)angle) * after_i - sin((double)angle) * after_j) + midX_pre;
				pre_j = (int)(sin((double)angle) * after_i + cos((double)angle) * after_j) + midY_pre;

				if(pre_i >= 0 && pre_i < highth && pre_j >= 0 && pre_j < width)//在原图范围内
					for(k=0; k<3; k++)
					{
						out.imgData[i * Rot_step + j*3 +k] = bmpImg.imgData[pre_i * step + pre_j*3 + k];
					}
                    // addr=at(&out,i,j);
                    //  *addr=0xFF;
			}
		}
        return out;
} 