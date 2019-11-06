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
#include "arm_linux_hardpatch.h"

void ShowbmpImage(Mat* mat,struct fb_var_screeninfo vinfo,struct fb_fix_screeninfo finfo,char *fbp)
{

   int x,y;
   u8* addr;
   long int location = 0;
  for(x=0;x<=mat->width;x++)
  for(y=0;y<=mat->highth;y++)
  {
         addr=at(mat,x,y);
  
         location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                 (y+vinfo.yoffset) * finfo.line_length;
         *(fbp + location) =    *(addr); /*  blue */
         *(fbp + location + 1) =*(addr+1);
         *(fbp + location + 2) =*(addr+2); /* red */
         *(fbp + location + 3) = 0x00;
         
  }
}

int main()
{
      int x,y;
      long int location = 0;
      Mat src,dst;
      int fbfd = 0;
      struct fb_var_screeninfo vinfo;
      struct fb_fix_screeninfo finfo;
      char *fbp;
      long int screensize = 0;
      Mat_Init();
      u8* addr;
      src=load("./picture/hole.bmp");
      dst=creatMapMat(src, 500,500);

      fbfd = open("/dev/fb0", O_RDWR);


        if (!fbfd) {
                printf("Error: cannot open framebuffer device.\n");
                exit(1);
        }
        printf("The framebuffer device was opened successfully.\n");

        /* Get fixed screen information */
        if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo)) {
                printf("Error reading fixed information.\n");
                exit(2);
        }

        /* Get variable screen information */
        if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo)) {
                printf("Error reading variable information.\n");
                exit(3);
        }
    
        /* Figure out the size of the screen in bytes */
        screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;
        /* Map the device to memory */
        
        fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED,
                fbfd, 0);
        if ((int)fbp == -1)
        {
            printf("Error: failed to map framebuffer device to memory.\n"); exit(4);
        }
        printf("The framebuffer device was mapped to memory successfully.\n");



      ShowbmpImage(&dst,vinfo,finfo,fbp);
     

  
//    save("./picture/test.bmp",&dst);


//printf("%d,%d,%d,%d",sizeof(BYTE),sizeof(WORD),sizeof(DWORD),sizeof(LONG));
   return 0; 
}

 
