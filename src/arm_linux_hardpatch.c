/*************************************************
Copyright © Yueyang Co. Ltd. 2019-2029. All rights reserved.
File name: arm_linux_hardpatch.c
Author： Yueyang
Version: V1.0
Description: LiteCV适配ARM_LINUX的硬件的补丁文件
Others: 
Log: 11.3 Yueyang
*************************************************/
#include "Mat.h"
#include "arm_linux_hardpatch.h"

#ifdef ARM_LINUX

#define R_MASK   0x0000FF
#define G_MASK   0x00FF00
#define B_MASK   0xFF0000

void LCD_DrawPoint(u32 x, u32 y,u32 color,struct fb_fix_screeninfo* finfo, struct fb_var_screeninfo* vinfo, char *pfb)
{
    long int location = 0;
    unsigned char index = 0;
    location = (x+vinfo->xoffset) * (vinfo->bits_per_pixel/8) +(y+vinfo->yoffset) * finfo->line_length;
     *(pfb + location) = (color&&R_MASK);
     *(pfb + location + 1) = (color&&G_MASK)>>8;
     *(pfb + location + 2) = (color&&B_MASK)>>16;
}




#endif 
