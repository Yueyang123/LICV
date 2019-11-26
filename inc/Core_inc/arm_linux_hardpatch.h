/*************************************************
Copyright © Yueyang Co. Ltd. 2019-2029. All rights reserved.
File name: arm_linux_hardpatch.c
Author： Yueyang
Version: V1.0
Description: LiteCV适配ARM_LINUX的硬件
Others: 
Log: 11.3 Yueyang
*************************************************/


#ifdef ARM_LINUX

void LCD_DrawPoint(unsigned int x, unsigned int y,struct fb_fix_screeninfo finfo, struct fb_var_screeninfo vinfo, char *pfb);
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,struct fb_fix_screeninfo finfo, struct fb_var_screeninfo vinfo, char *pfb);
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2,struct fb_fix_screeninfo finfo, struct fb_var_screeninfo vinfo, char *pfb);
void LCD_Draw_Circle(u16 x0,u16 y0,u8 r,struct fb_fix_screeninfo finfo, struct fb_var_screeninfo vinfo, char *fpb);
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p,struct fb_

#endif 