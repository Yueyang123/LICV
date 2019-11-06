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


int main()
{
     int i,j;
     Mat src,dst;

      int fbfd = 0;
      struct fb_var_screeninfo vinfo;
      struct fb_fix_screeninfo finfo;
      char *fbp = 0;
      
      Mat_Init();

      Lcd_Init(&vinfo,&finfo,fbp);

for(i=0;i<=800;i++)
for(j=0;j<=600;j++)
      LCD_DrawPoint(i, 
                    j,
                    0xFF0000,
                    &finfo,
                    &vinfo, 
                    pfb);

    //   src=load("./picture/hole.bmp");

  
    //    save("./picture/test.bmp",&dst);


//printf("%d,%d,%d,%d",sizeof(BYTE),sizeof(WORD),sizeof(DWORD),sizeof(LONG));
   return 0; 
}

 
