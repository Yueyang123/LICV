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
#include "Piclib.h"
#include <string.h>
#include <stdlib.h>
#ifdef SDL
#include "SDL.h"
#include "SDL_test_images.h"
#include "SDL_ex.h"

#endif // DEBUG


Mat Matload(char* dstname ,char * filename)
{
    int len=strlen(filename)/sizeof(char);
    char ext[3];
    Mat dst;
   if(filename[0]!='\"')
   {
      strncpy(ext,&filename[len-3],3);
      if((ext[0]=='b' && ext[1]=='m' && ext[2]=='p'))
      {
      printf("The file is  a bmp file.\n");
      dst=bmpload(dstname,filename);
      }
      else if((ext[0]=='j' && ext[1]=='p' && ext[2]=='g'))
      {
      printf("The file is  a jpg file.\n");
      dst=read_JPEG_file(dstname,filename);
      }
      else if ((ext[0]=='p' && ext[1]=='n' && ext[2]=='g'))
      {
       printf("The file is  a png file.\n");
       dst=read_PNG_file(dstname,filename);
      }
      return dst;
   }

}

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

   dst=Create("..\\picture\\test.bmp",cols_c,rows_c,3);

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

   #ifdef SDL//如果使用了SDL的库函数
      
   void ShowImage(Mat* mat,char* winname)
   {
    u32 x,y,color;
    u8* inaddr;
    SDL_Surface *imageSurface = NULL; // 申明用于加载图片的SDL_Surface
      if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
      }
      SDL_Window *window = SDL_CreateWindow(winname, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mat->width, mat->highth, SDL_WINDOW_ALLOW_HIGHDPI);
      if (NULL == window) {
      }

    imageSurface = SDL_GetWindowSurface(window);
    
    for(x=0;x<mat->width;x++)
    for(y=0;y<mat->highth;y++)
    {
      inaddr=at(mat,x,y);
      POINT p=GetPoint(x,y);
      color=RGB(*(inaddr),*(inaddr+1),*(inaddr+2));
      draw_point(imageSurface,p,color);
    }
    SDL_Event windowEvent;

        SDL_UpdateWindowSurface(window);
    

   //  imageSurface = NULL;
   //  SDL_DestroyWindow(window);
   }
      
   #else
      void ShowImage(Mat* mat,char * winname)
      {
         char cmd[266];
         strcpy(cmd,"start ");
         strcat(cmd,mat->PATH);
         printf("%s\n",cmd);
         system(cmd);
      }

   #endif




#endif 


#ifdef X86_LINUX

void ShowImage(Mat* mat)
{
   char cmd[266];
   strcpy(cmd,"display ");
   strcat(cmd,mat->PATH);
   printf("%s\n",cmd);
   system(cmd);
}
#endif 

#ifdef ARM_LINUX


#endif 


