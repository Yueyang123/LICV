/*************************************************
Copyright © Yueyang Co. Ltd. 2019-2029. All rights reserved.
File name: arm_linux_hardpatch.c
Author： Yueyang
Version: V1.0
Description: LiteCV适配ARM_LINUX的硬件
Others: 
Log: 11.3 Yueyang
*************************************************/

#include "cv.h"

#ifdef ARM_LINUX


void LCD_DrawPoint(u32 x, u32 y,u32 color,struct fb_fix_screeninfo finfo, struct fb_var_screeninfo vinfo, char *pfb);

#endif 