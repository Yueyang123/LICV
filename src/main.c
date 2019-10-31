/*
*版权所有 (C)2019,Yueyang.
*文件名称：main.c
*内容摘要：LiteCV基础测试函数
*当前版本：V1.0
*作者：杨越
*完成日期：20191020
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>
#include <process.h>

#include "bmp.h"
#include "cv.h"
#include "GeoTrans.h"

int main()
{
   Mat src;
   Mat dst;
   int i,j;
   Mat_INIT();
   src=load("F:\\myproject\\LiteCV\\picture\\lena.bmp");


   dst=imrotate(src,30);


   save("F:\\myproject\\LiteCV\\picture\\lena16.bmp",&dst);
   show(&dst);
   free(dst.PATH);
   free(dst.imgData);
   free(src.PATH);
   free(src.imgData);
}

 