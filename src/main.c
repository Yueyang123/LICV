/*************************************************
Copyright © Yueyang Co. Ltd. 2019-2029. All rights reserved.
File name: main.c
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
#include "Mat.h"
#include "GeoTrans.h"
#include "PointOr.h"
#include "MathOr.h"
#include "BasicGui.h"
#include "RGB2HSL.h"
#include "ColorDec.h"
#include "Piclib.h"

/* Prepare a dummy image. */
static void FillYuvImage(BYTE* pYuv, int nWidth, int nHeight, int nIndex)
{
	int x, y, i;
 
	i = nIndex;
 
	BYTE* pY = pYuv;
	BYTE* pU = pYuv + nWidth * nHeight;
	BYTE* pV = pYuv + nWidth * nHeight * 5 / 4;
 
	/* Y */
	for (y = 0; y < nHeight; y++)
	{
		for (x = 0; x < nWidth; x++)
		{
			pY[y * nWidth + x] = x + y + i * 3;
		}
	}
 
	/* Cb and Cr */
	for (y = 0; y < nHeight / 2; y++)
	{
		for (x = 0; x < nWidth / 2; x++)
		{
			pU[y * (nWidth/2) + x] = 128 + y + i * 2;
			pV[y * (nWidth/2) + x] = 64 + x + i * 5;
		}
	}
}
 


// int main()
// {
//      Mat dst;
//      Mat_Init;
//      u8* inaddr;
//      int x,y;
//      Mat src1 =Load("..\\picture\\test.bmp","..\\picture\\lena.png");
//      Mat src2 =Load("..\\picture\\test1.bmp","..\\picture\\lena.jpg");
//      save("..\\picture\\test.bmp",&src1);
//      save("..\\picture\\test1.bmp",&src2);
//      Show(&src1);
//      Show(&src2);
//      return 0; 
// }

 