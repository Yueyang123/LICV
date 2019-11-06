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


int ReadbmpPixelData(char *filepath,BYTE *imgData)
{
   BITMAPINFOHEADER bmih;
   BITMAPFILEHEADER bmfh;
   BYTE *data;
   FILE *fp;
   int n;
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
   dwLineBytes=GetLineBytes(width,bitCount);

   data=(BYTE*)Li_malloc(dwLineBytes*height*sizeof(BYTE));
   if(!data)
   {
      printf("Can not allocate memory for the pixel data.\n");
      return -1;
   }
   fp=fopen(filepath,"rb");
   if(!fp)
   {
      printf("Can not open the file: %s\n",filepath);
      Li_free(data);
      return -1;
   }
   if(bitCount==8)
   {
      fseek(fp,bmfh.bfOffBits,SEEK_SET);
   }
   else if(bitCount==24)
   {
      fseek(fp,bmfh.bfOffBits,SEEK_SET);
   }
   else if(bitCount==16)
   {
      fseek(fp,bmfh.bfOffBits,SEEK_SET);
   }
   else
   {
      printf("DO NOT SUPPORT THIS KIND OF FILE\n");
      return -1;
   }
   
   if(fread(data,dwLineBytes*height*sizeof(BYTE),1,fp)!=1)
   {
      printf("Can not read the pixel data.\n");
      Li_free(data);
      fclose(fp);
      return -1;
   }
   Li_memcpy(imgData,data,dwLineBytes*height*sizeof(BYTE));
   Li_free(data);
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
      if(bitCount==8)
      {
         for(i=0;i<height;i++)
         {
         for(j=0;j<width;j++)
         {
         p=*(imgData+dwLineBytes*(height-1-i)+j);
         printf("%d,",p);
         }
         printf("\n");
         }
      }
      else if(bitCount==24)
      {
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
      else
      {
         printf("Only supported: 8 or 24 bits.\n");
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


Mat bmpload(char *filepath)
{
    int i,q;
    int bitCount;
    DWORD dwLineBytes;
    Mat mat;
    i=CheckbmpFilePath(filepath);
    i=0;
    mat.PATH=Li_malloc(100);
    strcpy(mat.PATH,filepath);

   
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
     PrintbmpFileHeader(&mat.bmf);
     PrintbmpInfoHeader(&mat.bmi);
     mat.highth=mat.bmi.biHeight;
     mat.width=mat.bmi.biWidth;
     bitCount=mat.bmi.biBitCount;
     mat.pictype=mat.bmi.biBitCount/8;
     dwLineBytes=GetLineBytes(mat.width,bitCount);
     mat.imgData=(BYTE*)Li_malloc(dwLineBytes*(mat.highth)*sizeof(BYTE));
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


int bmpprocess(Mat* mat,int width,int highth,u32 color)
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

u8* bmpat(Mat* mat,int width,int highth)
{
   u32 offset;  
	   DWORD dwLineBytes=GetLineBytes(mat->width,24);
	   offset=dwLineBytes*(mat->highth-1-highth)+width*3;

	   return mat->imgData+offset;
	

}


int SaveAsbmpImage(char *filepath,Mat* mat)
{
   FILE *fp;
   RGBQUAD pal[256];
   int i;
   int height;
   DWORD dwLineBytes;
   Mat* dst;
   height=mat->bmi.biHeight;
   dwLineBytes=GetLineBytes(mat->bmi.biWidth,mat->bmi.biBitCount);
   strcpy(mat->PATH,filepath);
   fp=fopen(filepath,"wb");
   if(!fp)
   {
      printf("Error: Can not open the file:%s\n",filepath);
   }

   for(i=0;i<256;i++)
   {
      pal[i].rgbReserved=0;
      pal[i].rgbBlue=i;
      pal[i].rgbGreen=i;
      pal[i].rgbRed=i;
   }

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

   if(mat->bmi.biBitCount==8)
   {
      if(fwrite(pal,sizeof(RGBQUAD),256,fp)!=256)
      {
      printf("Error: can not write the color palette.\n");
      fclose(fp);
      }
   }

   if(fwrite(mat->imgData,height*dwLineBytes,1,fp)!=1)
   {
      printf("Error: can not write the pixel data.\n");
      fclose(fp);
   }

   fclose(fp);
   printf("Save As the image successfully.\n");

   return 0;

}

Mat bmpcopy(Mat mat)
{
   Mat out;
   out.bmf=mat.bmf;
   out.bmi=mat.bmi;
   out.highth=mat.highth;
   out.width=mat.width;
   out.pictype=mat.pictype;
   out.PATH=Li_malloc(100);
   strcpy(out.PATH,mat.PATH);
   out.imgData=(BYTE*)Li_malloc(mat.highth*mat.width*3);
   Li_memcpy(out.imgData,mat.imgData,mat.highth*mat.width*3);
   return out;

}

void bmpdestory(Mat* mat)
{
   free(mat->PATH);
   free(mat->imgData);
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

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <string.h>





#endif 
