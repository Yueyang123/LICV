/*
*��Ȩ���� (C)2019,Yueyang.
*�ļ����ƣ�main.c
*����ժҪ��LiteCV�������Ժ���
*��ǰ�汾��V1.0
*���ߣ���Խ
*������ڣ�20191020
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#include "bmp.h"
#include "cv.h"
#include "GeoTrans.h"

int main()
{
   Mat src;
   Mat dst;
   int i,j;
   Mat_INIT();
   src=load("F:\\myproject\\LiteCV\\picture\\lena0.bmp");

   dst=imrotate(src,30);
   save("F:\\myproject\\LiteCV\\picture\\lena.bmp",&dst);
   show(&dst);
   destory(&dst);
   destory(&src);
   return 0; 
}

 