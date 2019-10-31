/*
*��Ȩ���� (C)2019,Yueyang.
*�ļ����ƣ�main.c
*����ժҪ��LiteCV���α任
*��ǰ�汾��V1.0
*���ߣ���Խ
*������ڣ�20191020
*/

#include "cv.h"
#include "bmp.h"
#include "GeoTrans.h"
#include <math.h>

Mat imrotate(Mat bmpImg,int Angle)
{
    double angle;//Ҫ��ת�Ļ�����
    int width = 0;
    int highth = 0;
    int step = 0;
	int Rot_step = 0;
	int channels = 3;
    int i, j, k;
    u8* addr;
	width = bmpImg.width;
	highth = bmpImg.highth;
    int midX_pre,midY_pre,midX_aft,midY_aft;//��תǰ������ĵ������
    midX_pre = width / 2;
    midY_pre = highth / 2;
    int pre_i,pre_j,after_i,after_j;//��תǰ���Ӧ�����ص�����
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
        
        
        
        //����任
		for(i = 0;i < bmpImg.highth;i++)
		{
			for(j = 0;j < bmpImg.width;j++)
			{
				after_i = i - midX_aft;
				after_j = j - midY_aft;
				pre_i = (int)(cos((double)angle) * after_i - sin((double)angle) * after_j) + midX_pre;
				pre_j = (int)(sin((double)angle) * after_i + cos((double)angle) * after_j) + midY_pre;

				if(pre_i >= 0 && pre_i < highth && pre_j >= 0 && pre_j < width)//��ԭͼ��Χ��
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