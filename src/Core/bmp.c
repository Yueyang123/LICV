/*************************************************
Copyright © Yueyang Co. Ltd. 2019-2029. All rights reserved.
File name: bmp.c
Author： Yueyang
Version: V1.0
Description: 提供对于bmp文件的操作函数
Others: 
Log: 11.3 Yueyang
*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "string.h"
#include "bmp.h"



int ReadbmpFileHeader(char *filepath,BITMAPFILEHEADER *bmfh)
{
   FILE *fp;
   fp=fopen(filepath,"rb");
   if(!fp)
   {
      printf("Can not open the file:%s\n",filepath);
      return -1;
   }
   if(fread(&bmfh->bfType,sizeof(WORD),1,fp)!=1)
   {
      printf("Can not read bfType in the file header.\n");
      fclose(fp);
      return -1;
   }
   if(fread(&bmfh->bfSize,sizeof(DWORD),1,fp)!=1)
   {
      printf("Can not read bfSize in the file header.\n");
      fclose(fp);
      return -1;
   }
   if(fread(&bmfh->bfReserved1,sizeof(WORD),1,fp)!=1)
   {
      printf("Can not read bfReserved1 in the file header.\n");
      fclose(fp);
      return -1;
   }
   if(fread(&bmfh->bfReserved2,sizeof(WORD),1,fp)!=1)
   {
      printf("Can not read bfReserved2 in the file header.\n");
      fclose(fp);
      return -1;
   }
   if(fread(&bmfh->bfOffBits,sizeof(DWORD),1,fp)!=1)
   {
      printf("Can not read bfOffBits in the file header.\n");
      fclose(fp);
      return -1;
   }
   fclose(fp);
   return 0;
}


int ReadbmpInfoHeader(char *filepath,BITMAPINFOHEADER *bmih)
{
   FILE *fp;
   fp=fopen(filepath,"rb");
   if(!fp)
   {
      printf("Can not open the file:%s\n",filepath);
      return -1;
   }
   fseek(fp,14,SEEK_SET);
   if(fread(&bmih->biSize,sizeof(DWORD),1,fp)!=1)
   {
      printf("Can not read biSize in the info header.\n");
      fclose(fp);
      return -1;
   }
   if(fread(&bmih->biWidth,sizeof(LONG),1,fp)!=1)
   {
      printf("Can not read biWidth in the info header.\n");
      fclose(fp);
      return -1;
   }
   if(fread(&bmih->biHeight,sizeof(LONG),1,fp)!=1)
   {
      printf("Can not read biHeight in the info header.\n");
      fclose(fp);
      return -1;
   }
   if(fread(&bmih->biPlanes,sizeof(WORD),1,fp)!=1)
   {
      printf("Can not read biPlanes in the info header.\n");
      fclose(fp);
      return -1;
   }
   if(fread(&bmih->biBitCount,sizeof(WORD),1,fp)!=1)
   {
      printf("Can not read biBitCount in the info header.\n");
      fclose(fp);
      return -1;
   }
   if(fread(&bmih->biCompression,sizeof(DWORD),1,fp)!=1)
   {
      printf("Can not read biCompression in the info header.\n");
      fclose(fp);
      return -1;
   }
   if(fread(&bmih->biSizeImage,sizeof(DWORD),1,fp)!=1)
   {
      printf("Can not read biSizeImage in the info header.\n");
      fclose(fp);
      return -1;
   }
   if(fread(&bmih->biXPelsPerMeter,sizeof(LONG),1,fp)!=1)
   {
      printf("Can not read biXPelsPerMeter in the info header.\n");
      fclose(fp);
      return -1;
   }
   if(fread(&bmih->biYPelsPerMeter,sizeof(LONG),1,fp)!=1)
   {
      printf("Can not read biYPelsPerMeter in the info header.\n");
      fclose(fp);
      return -1;
   }
   if(fread(&bmih->biClrUsed,sizeof(DWORD),1,fp)!=1)
   {
      printf("Can not read biClrUsed in the info header.\n");
      fclose(fp);
      return -1;
   }
   if(fread(&bmih->biClrImportant,sizeof(DWORD),1,fp)!=1)
   {
      printf("Can not read biClrImportant in the info header.\n");
      fclose(fp);
      return -1;
   }
   fclose(fp);
   return 0;
}

//注意这里的指针必须已经完成了内存申请
//读取BMP图片的像素值，仅以三通道的形式保存
int ReadbmpPixelData(char *filepath,BYTE *imgData)
{
   BITMAPINFOHEADER bmih;
   BITMAPFILEHEADER bmfh;
   BYTE *data;
   FILE *fp;
   u8 R, G, B;
   u16 pixel;
   int n,i;
   int width;
   int height;
   int bitCount;
   DWORD dwLineBytes;
   n=ReadbmpFileHeader(filepath,&bmfh);
   if(n==-1)
   {
      printf("Can not read the file header of the BMP file.\n");
      return -1;
   }
   n=ReadbmpInfoHeader(filepath,&bmih);
   if(n==-1)
   {
      printf("Can not read the info header of the BMP file.\n");
      return -1;
   }
   width=bmih.biWidth;
   height=bmih.biHeight;
   bitCount=bmih.biBitCount;

   fp=fopen(filepath,"rb");
   if(!fp)
   {
      printf("Can not open the file: %s\n",filepath);
      free(data);
      return -1;
   }
   fseek(fp,bmfh.bfOffBits,SEEK_SET);

   if(bitCount==32)
   {
        dwLineBytes=4*width;
         data=(BYTE*)malloc(dwLineBytes*height*sizeof(BYTE));
         if(!data)
         {
            printf("Can not allocate memory for the pixel data.\n");
            return -1;
         }
         if(fread(data,dwLineBytes*height*sizeof(BYTE),1,fp)!=1)
         {
            printf("Can not read the pixel data.\n");
            free(data);
            fclose(fp);
            return -1;
         }
         for(i=0;i<width*height;i++)
         {
         R = *(data+4*i+3);
         G = *(data+4*i+2);
         B = *(data+4*i+1);
         *(imgData+3*i)=B;
         *(imgData+3*i+1)=G;
         *(imgData+3*i+2)=R;
         }

   }
   else if(bitCount==24)//对于RGB888直接进行数据拷贝即可
   {
      dwLineBytes=3*width;
         data=(BYTE*)malloc(dwLineBytes*height*sizeof(BYTE));
         if(!data)
         {
            printf("Can not allocate memory for the pixel data.\n");
            return -1;
         }
      if(fread(data,dwLineBytes*height*sizeof(BYTE),1,fp)!=1)
      {
         printf("Can not read the pixel data.\n");
         free(data);
         fclose(fp);
         return -1;
      }
   memcpy(imgData,data,dwLineBytes*height*sizeof(BYTE));
   }
   else if(bitCount==16)//对于RGB565的图像需要先转化为三色道的形式
   {
      dwLineBytes=2*width;

         data=(BYTE*)malloc(dwLineBytes*height*sizeof(BYTE));
         if(!data)
         {
            printf("Can not allocate memory for the pixel data.\n");
            return -1;
         }
      if(fread(data,dwLineBytes*height*sizeof(BYTE),1,fp)!=1)
      {
         printf("Can not read the pixel data.\n");
         free(data);
         fclose(fp);
         return -1;
      }
      for(i=0;i<width*height;i++)
      {
      pixel=(*(data+1+i*2))<<8|(*(data+i*2));
      R = (pixel&RGB565_R)>>11;
      G = (pixel&RGB565_G)>>5;
      B = (pixel&RGB565_B);
      *(imgData+3*i)=B;
      *(imgData+3*i+1)=G;
      *(imgData+3*i+2)=R;
      }
   }
   else if(bitCount==8)//对于8位的图像需要先转化为三色道的形式
   {
      dwLineBytes=1*width;
         data=(u8*)malloc(dwLineBytes*height);
         if(!data)
         {
            printf("Can not allocate memory for the pixel data.\n");
            return -1;
         }
      if(fread(data,dwLineBytes*height,1,fp)!=1)
      {
         printf("Can not read the pixel data.\n");
         printf("%d",dwLineBytes*height);
         free(data);
         fclose(fp);
         return -1;
      }

      for(i=0;i<width*height;i++)
      {
      pixel=*(data+i); 
      R = (u8)(pixel);
      G = (u8)(pixel);
      B = (u8)(pixel);
      *(imgData+3*i)=R;
      *(imgData+3*i+1)=G;
      *(imgData+3*i+2)=B;
      }
   }
   else
   {
      printf("NO WE DONT SUPPORT THIS KIND OF BMP\n");
   }
   

   free(data);
   fclose(fp);
   return 0;
}

void PrintbmpFileHeader(BITMAPFILEHEADER *bmfh)
{
   printf("The contents in the file header of the BMP file:\n");
   printf("bfOffBits: %ld\n",bmfh->bfOffBits);
   printf("bfReserved1: %ld\n",bmfh->bfReserved1);
   printf("bfReserved2: %ld\n",bmfh->bfReserved2);
   printf("bfSize: %ld\n",bmfh->bfSize);
   printf("bfType: %ld\n",bmfh->bfType);
}

void PrintbmpInfoHeader(BITMAPINFOHEADER *bmih)
{
   printf("The content in the info header of the BMP file:\n");
   printf("biBitCount: %ld\n",bmih->biBitCount);
   printf("biClrImportant: %ld\n",bmih->biClrImportant);
   printf("biClrUsed: %ld\n",bmih->biClrUsed);
   printf("biCompression: %ld\n",bmih->biCompression);
   printf("biHeight: %ld\n",bmih->biHeight);
   printf("biPlanes: %ld\n",bmih->biPlanes);
   printf("biSize: %ld\n",bmih->biSize);
   printf("biSizeImage: %ld\n",bmih->biSizeImage);
   printf("biWidth: %ld\n",bmih->biWidth);
   printf("biXPelsPerMeter: %ld\n",bmih->biXPelsPerMeter);
   printf("biYPelsPerMeter: %ld\n",bmih->biYPelsPerMeter);
}

LONG GetLineBytes(int imgWidth,int bitCount)
{
   return (imgWidth*bitCount+31)/32*4;
}

void PrintbmpPixelData(BYTE *imgData,int width,int height,int bitCount)
{
   int i;
   int j;
   int p;
   DWORD dwLineBytes=GetLineBytes(width,bitCount);

      for(i=0;i<height;i++)
      {
        for(j=0;j<width*3;j++)
         {
         printf("(");
         p=*(imgData+dwLineBytes*(height-1-i)+j);
         printf("%d,",p);
         j++;
         p=*(imgData+dwLineBytes*(height-1-i)+j);
         printf("%d,",p);
         j++;
         p=*(imgData+dwLineBytes*(height-1-i)+j);
         printf("%d) ",p);
         }
         printf("\n");
      }
      
 }


 int CheckbmpFilePath(char *filepath)
 {
   FILE *fp;
   int len=strlen(filepath)/sizeof(char);
   char ext[3];
   if(filepath[0]!='\"')
   {
      strncpy(ext,&filepath[len-3],3);
      if(!(ext[0]=='b' && ext[1]=='m' && ext[2]=='p'))
      {
      printf("Error: The file is not a BMP file.\n");
      printf("Error: The extention of the filename must be 'bmp',not 'BMP'\n");
      return -1;
      }
      fp=fopen(filepath,"r");
      if(!fp)
      {
      printf("Error: The path is not correct.\n");
      return -1;
      }
      fclose(fp);
   }
   else
   {
      printf("Error: The path must not include blank space.\n");
      return -1;
   }
   return 0;
}


Mat bmpload(char* dstname,char *filepath)
{
    int i,q;
    int bitCount;
    DWORD dwLineBytes;
    Mat mat;
    i=CheckbmpFilePath(filepath);
    i=0;
    mat.PATH=malloc(100);
    strcpy(mat.PATH,dstname);

   
     i=ReadbmpFileHeader(filepath,&mat.bmf);
     if(i!=-1)
     {
      printf("Read the file header successfully.\n");
     }
     else
     {
      printf("Read the file header failed.\n");
      q=1;
     }
     i=ReadbmpInfoHeader(filepath,&mat.bmi);
     if(i!=-1)
     {
      printf("Read the info header successfully.\n");
     }
     else
     {
      printf("Read the info header failed.\n");
      q=1;
     }

   #ifdef DEBUG
     PrintbmpFileHeader(&mat.bmf);
     PrintbmpInfoHeader(&mat.bmi);
   #endif // DEBUG

     mat.highth=mat.bmi.biHeight;
     mat.width=mat.bmi.biWidth;
     bitCount=mat.bmi.biBitCount;
     mat.pictype=mat.bmi.biBitCount/8;
     dwLineBytes=3*mat.width;
     mat.imgData=(BYTE*)malloc(dwLineBytes*(mat.highth)*sizeof(BYTE));
     if(!mat.imgData)
     {
      printf("Can not allocate memory for the image.\n");
      q=1;
     }
     i=ReadbmpPixelData(filepath,mat.imgData);
     if(i==-1)
     {
      printf("Read the pixel data failed.\n");
      q=1;
     }
     else
     {
      printf("Read the pixel data successfully.\n");
     }
     return mat;
}


//将图片以RGB888的形式存储
int SaveAsbmp24Image(char *filepath,Mat* mat)
{
   FILE *fp;
   RGBQUAD pal[256];
   int i;
   int height;
   DWORD dwLineBytes;
   Mat* dst;
   height=mat->bmi.biHeight;
   dwLineBytes=3*mat->width;

   strcpy(mat->PATH,filepath);
      fp=fopen(filepath,"wb");
      if(!fp)
      {
         printf("Error: Can not open the file:%s\n",filepath);
      }

   if(mat->bmi.biBitCount==24)
   {
      if(fwrite(&mat->bmf.bfType,sizeof(WORD),1,fp)!=1)
      {
         printf("Can not write bfType in the file header.\n");
         fclose(fp);
      }

      if(fwrite(&mat->bmf.bfSize,sizeof(DWORD),1,fp)!=1)
      {
         printf("Can not write bfSize in the file header.\n");
         fclose(fp);
      }

      if(fwrite(&mat->bmf.bfReserved1,sizeof(WORD),1,fp)!=1)
      {
         printf("Can not write bfReserved1 in the file header.\n");
         fclose(fp);
      }

      if(fwrite(&mat->bmf.bfReserved2,sizeof(WORD),1,fp)!=1)
      {
         printf("Can not write bfReserved2 in the file header.\n");
         fclose(fp);
      }

      if(fwrite(&mat->bmf.bfOffBits,sizeof(DWORD),1,fp)!=1)
      {
         printf("Can not write bfOffBits in the file header.\n");
         fclose(fp);
      }
      if(fwrite(&mat->bmi.biSize,sizeof(DWORD),1,fp)!=1)
      {
         printf("Can not write biSize in the info header.\n");
         fclose(fp);
      }

      if(fwrite(&mat->bmi.biWidth,sizeof(LONG),1,fp)!=1)
      {
         printf("Can not write biWidth in the info header.\n");
         fclose(fp);
      }

      if(fwrite(&mat->bmi.biHeight,sizeof(LONG),1,fp)!=1)
      {
         printf("Can not write biHeight in the info header.\n");
         fclose(fp);
      }

      if(fwrite(&mat->bmi.biPlanes,sizeof(WORD),1,fp)!=1)
      {
         printf("Can not write biPlanes in the info header.\n");
         fclose(fp);
      }

      if(fwrite(&mat->bmi.biBitCount,sizeof(WORD),1,fp)!=1)
      {
         printf("Can not write biBitCount in the info header.\n");
         fclose(fp);
      }

      if(fwrite(&mat->bmi.biCompression,sizeof(DWORD),1,fp)!=1)
      {
         printf("Can not write biCompression in the info header.\n");
         fclose(fp);
      }

      if(fwrite(&mat->bmi.biSizeImage,sizeof(DWORD),1,fp)!=1)
      {
         printf("Can not write biSizeImage in the info header.\n");
         fclose(fp);
      }

      if(fwrite(&mat->bmi.biXPelsPerMeter,sizeof(LONG),1,fp)!=1)
      {
         printf("Can not write biXPelsPerMeter in the info header.\n");
         fclose(fp);
      }

      if(fwrite(&mat->bmi.biYPelsPerMeter,sizeof(LONG),1,fp)!=1)
      {
         printf("Can not write biYPelsPerMeter in the info header.\n");
         fclose(fp);
      }

      if(fwrite(&mat->bmi.biClrUsed,sizeof(DWORD),1,fp)!=1)
      {
         printf("Can not write biClrUsed in the info header.\n");
         fclose(fp);
      }

      if(fwrite(&mat->bmi.biClrImportant,sizeof(DWORD),1,fp)!=1)
      {
         printf("Can not write biClrImportant in the info header.\n");
         fclose(fp);
      }
      if(fwrite(mat->imgData,height*dwLineBytes,1,fp)!=1)
      {
         printf("Error: can not write the pixel data.\n");
         fclose(fp);
      }
   }
   else if(mat->bmi.biBitCount==8)
   {
      if(fwrite(&mat->bmf.bfType,sizeof(WORD),1,fp)!=1)
      {
         printf("Can not write bfType in the file header.\n");
         fclose(fp);
      }
      mat->bmf.bfSize*=3;
      if(fwrite(&mat->bmf.bfSize,sizeof(DWORD),1,fp)!=1)
      {
         printf("Can not write bfSize in the file header.\n");
         fclose(fp);
      }

      if(fwrite(&mat->bmf.bfReserved1,sizeof(WORD),1,fp)!=1)
      {
         printf("Can not write bfReserved1 in the file header.\n");
         fclose(fp);
      }

      if(fwrite(&mat->bmf.bfReserved2,sizeof(WORD),1,fp)!=1)
      {
         printf("Can not write bfReserved2 in the file header.\n");
         fclose(fp);
      }
      mat->bmf.bfOffBits=54;
      if(fwrite(&mat->bmf.bfOffBits,sizeof(DWORD),1,fp)!=1)
      {
         printf("Can not write bfOffBits in the file header.\n");
         fclose(fp);
      }
      if(fwrite(&mat->bmi.biSize,sizeof(DWORD),1,fp)!=1)
      {
         printf("Can not write biSize in the info header.\n");
         fclose(fp);
      }

      if(fwrite(&mat->bmi.biWidth,sizeof(LONG),1,fp)!=1)
      {
         printf("Can not write biWidth in the info header.\n");
         fclose(fp);
      }

      if(fwrite(&mat->bmi.biHeight,sizeof(LONG),1,fp)!=1)
      {
         printf("Can not write biHeight in the info header.\n");
         fclose(fp);
      }

      if(fwrite(&mat->bmi.biPlanes,sizeof(WORD),1,fp)!=1)
      {
         printf("Can not write biPlanes in the info header.\n");
         fclose(fp);
      }
      mat->bmi.biBitCount=24;
      if(fwrite(&mat->bmi.biBitCount,sizeof(WORD),1,fp)!=1)
      {
         printf("Can not write biBitCount in the info header.\n");
         fclose(fp);
      }

      if(fwrite(&mat->bmi.biCompression,sizeof(DWORD),1,fp)!=1)
      {
         printf("Can not write biCompression in the info header.\n");
         fclose(fp);
      }
      mat->bmi.biSizeImage*=3;
      if(fwrite(&mat->bmi.biSizeImage,sizeof(DWORD),1,fp)!=1)
      {
         printf("Can not write biSizeImage in the info header.\n");
         fclose(fp);
      }

      if(fwrite(&mat->bmi.biXPelsPerMeter,sizeof(LONG),1,fp)!=1)
      {
         printf("Can not write biXPelsPerMeter in the info header.\n");
         fclose(fp);
      }

      if(fwrite(&mat->bmi.biYPelsPerMeter,sizeof(LONG),1,fp)!=1)
      {
         printf("Can not write biYPelsPerMeter in the info header.\n");
         fclose(fp);
      }

      if(fwrite(&mat->bmi.biClrUsed,sizeof(DWORD),1,fp)!=1)
      {
         printf("Can not write biClrUsed in the info header.\n");
         fclose(fp);
      }

      if(fwrite(&mat->bmi.biClrImportant,sizeof(DWORD),1,fp)!=1)
      {
         printf("Can not write biClrImportant in the info header.\n");
         fclose(fp);
      }
      
      if(fwrite(mat->imgData,height*dwLineBytes,1,fp)!=1)
      {
         printf("Error: can not write the pixel data.\n");
         fclose(fp);
      }


   }

   else
   {
      if(fwrite(mat->imgData,height*dwLineBytes,1,fp)!=1)
      {
         printf("Error: can not write the pixel data.\n");
         fclose(fp);
      }
   }

   fclose(fp);
   printf("Save As the image successfully.\n");

   return 0;

}


#ifdef WINDOWS

void ShowbmpImage(Mat* mat)
{
   char cmd[266];
   strcpy(cmd,"start ");
   strcat(cmd,mat->PATH);
   printf("%s\n",cmd);
   system(cmd);
}

#endif 


#ifdef X86_LINUX

void ShowbmpImage(Mat* mat)
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