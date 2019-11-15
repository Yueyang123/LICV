/*************************************************
Copyright © Yueyang Co. Ltd. 2019-2029. All rights reserved.
File name: Mat.c
Author： Yueyang
Version: V1.0
Description: 提供Mat结构体
Others: 
Log: 11.3 Yueyang
*************************************************/

#include "bmp.h"
#include "cv.h"
#include "GeoTrans.h"
#include <string.h>
#include <stdlib.h>

//创建一个空白的图片类
Mat MatCreate(u8* filepath,u16 width,u16 height,u8 type)
{
    Mat mat;
    mat.bmi.biBitCount=type*8;
    mat.bmi.biSize=sizeof(BITMAPINFOHEADER);
    mat.width=width;
    mat.bmi.biWidth=width;
    mat.highth=height;
    mat.bmi.biHeight=height;
    mat.bmi.biPlanes=1;
    mat.bmi.biCompression=0;
    mat.bmi.biSizeImage=height*width*type;
    mat.bmi.biClrUsed=0;
    mat.bmi.biClrImportant=0;
    mat.bmi.biXPelsPerMeter=2874;
    mat.bmi.biYPelsPerMeter=2874;

    mat.bmf.bfType=((u16)'M'<<8)+'B';
    mat.bmf.bfSize=786486;
    mat.bmf.bfOffBits=54;
    mat.imgData=malloc(height*width*type);
    mat.PATH=malloc(100);
    strcpy(mat.PATH,filepath);
    return mat;
}



Mat Matcopy(Mat* mat)
{
   Mat out;
   out.bmf=mat->bmf;
   out.bmi=mat->bmi;
   out.highth=mat->highth;
   out.width=mat->width;
   out.pictype=mat->pictype;
   out.PATH=malloc(100);
   strcpy(out.PATH,mat->PATH);
   out.imgData=(BYTE*)malloc(mat->highth*mat->width*3);
   memcpy(out.imgData,mat->imgData,mat->highth*mat->width*3);
   return out;

}

void Matdestory(Mat* mat)
{
   free(mat->PATH);
   free(mat->imgData);
}



int Matchange(Mat* mat,int width,int highth,u32 color)
{
   u32 offset;
   u8 R=(u8)(color);
   u8 G=(u8)(((WORD)(color)) >> 8);
   u8 B=(u8)((color)>>16);
   DWORD dwLineBytes=GetLineBytes(mat->width,24);
   offset=dwLineBytes*(mat->highth-1-highth)+width*3;
   *(mat->imgData+offset)=R;
   *(mat->imgData+offset+1)=G;
   *(mat->imgData+offset+2)=B;
   return 0;
}

u8* Matat(Mat* mat,int width,int highth)
{
   u32 offset;
   DWORD dwLineBytes=GetLineBytes(mat->width,24);
   offset=dwLineBytes*(mat->highth-1-highth)+width*3;
   return mat->imgData+offset;
}



/***********************************************
*name:         	int RGB2HSV(int R,int G,int B)
*parameter:    	int R,int G,int B
*function:     	convert RGB to HSV
*return:       	返回关于HSV对于红色的一个加权
*reserved:
***********************************************/
int RGB2HSV(int R,int G,int B)						//R'G'B变量类型可改。
{
	float maxRGB,minRGB,des;
	float H,S,V;
	int Hi,Si,Vi;
	int RedHSV;

	maxRGB=((R>=G)?R:G);							//the maximum
	maxRGB=((maxRGB>=B)?maxRGB:B);
	minRGB=((R<=G)?R:G);							//the minimum
	minRGB=((minRGB<=B)?minRGB:B);
	des=maxRGB-minRGB;

	V=maxRGB;													//the value of V
	Vi=(int)(V*366/255);							//force to int

	if(maxRGB==0)											//the value of S
		S=0;
	else
		S=1-minRGB/maxRGB;
	Si=(int)(S*360);									//force to int

	if(maxRGB==minRGB)								//the value of H
		H=0;
	else if((maxRGB==R)&&(G>=B))
		H=60*(G-B)/des;
	else if((maxRGB==R)&&(G<B))
		H=60*(G-B)/des+360;
	else if(maxRGB==G)
		H=60*(B-R)/des+120;
	else if(maxRGB==B)
		H=60*(R-G)/des+240;
	else
		;
	if(H<0)
		H=H+360;

	if((H>=0)&&(H<=60))								//对于红色进行加权
		H=60-H;
	else if((H>=300)&&(H<=360))
		H=360-H;
	else
		H=0;
	Hi=(int)H*60;

	if((H>60)&&(H<300))								//the color is not red
		RedHSV=0;
	else											//the color is red
		RedHSV=Hi+Si+Vi;
	return(RedHSV);
}





/**
 * @fn      Mat MatReshape(Mat src,u32 cols_c,int rows_c)
 *
 * @brief   图像调整大小的函数
 *          该过程没有插值处理
 *
 * @author  Yueyang
 * @date    2019/11/13
 *
 * @param   src         The picture type
 *          rows_c      图像的高度对应y
 *          cols_c      图像的宽度对应x
 * @return  A picture type
 */
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
      *inaddr=*outaddr;
      *(inaddr+1)=*(outaddr+1);
      *(inaddr+2)=*(outaddr+2);
    }
    return dst;

}




#ifdef WINDOWS

#endif

#ifdef X86_LINUX

#endif

#ifdef ARM_LINUX

#endif

#ifdef ARM_NONE

#endif




