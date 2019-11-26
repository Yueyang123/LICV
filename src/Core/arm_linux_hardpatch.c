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

#ifdef ARM_LINUX




void LCD_DrawPoint(unsigned int x, unsigned int y,struct fb_fix_screeninfo finfo, struct fb_var_screeninfo vinfo, char *pfb)
{
    long int location = 0;
    unsigned char index = 0;
    location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +(y+vinfo.yoffset) * finfo.line_length;
     *(pfb + location) = white[index];
     *(pfb + location + 1) = white[index+1];
     *(pfb + location + 2) = white[index+2];
}

void LCD_Clear(char *pfb)
{
    u32 i;
    for(i=0;i<=screensize*3;i++)
    {
      *(pfb + i)=0xff;
    }
}

//x1,y1:起点坐标
//x2,y2:终点坐标
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2,struct fb_fix_screeninfo finfo, struct fb_var_screeninfo vinfo, char *pfb)
{
    u16 t;
    int xerr=0,yerr=0,delta_x,delta_y,distance;
    int incx,incy,uRow,uCol;
    delta_x=x2-x1; //计算坐标增量
    delta_y=y2-y1;
    uRow=x1;
    uCol=y1;
    if(delta_x>0)incx=1; //设置单步方向
    else if(delta_x==0)incx=0;//垂直线
    else {incx=-1;delta_x=-delta_x;}
    if(delta_y>0)incy=1;
    else if(delta_y==0)incy=0;//水平线
    else{incy=-1;delta_y=-delta_y;}
    if( delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴
    else distance=delta_y;
    for(t=0;t<=distance+1;t++ )//画线输出
    {
        LCD_DrawPoint(uRow, uCol, finfo, vinfo, pfb);
        xerr+=delta_x ;
        yerr+=delta_y ;
        if(xerr>distance)
        {
            xerr-=distance;
            uRow+=incx;
        }
        if(yerr>distance)
        {
            yerr-=distance;
            uCol+=incy;
        }
    }
}

void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,struct fb_fix_screeninfo finfo, struct fb_var_screeninfo vinfo, char *pfb)
{
    u8 temp,t1,t;
    u16 y0=y;
    u8 csize=(size/8+((size%8)?1:0))*(size/2);		//得到字体一个字符对应点阵集所占的字节数
    num=num-' ';//得到偏移后的值（ASCII字库是从空格开始取模，所以-' '就是对应字符的字库）
    for(t=0;t<csize;t++)
    {
        if(size==12)temp=asc2_1206[num][t]; 	 	//调用1206字体
        else if(size==16)temp=asc2_1608[num][t];	//调用1608字体
        else if(size==24)temp=asc2_2412[num][t];	//调用2412字体
        else if(size==32)temp=asc2_3216[num][t];	//调用3216字体
        else return;								//没有的字库
        for(t1=0;t1<8;t1++)
        {
            if(temp&0x80)LCD_DrawPoint(x,y,finfo, vinfo, pfb);
            temp<<=1;
            y++;
            if(y>=1024)return;		//超区域了
            if((y-y0)==size)
            {
                y=y0;
                x++;
                if(x>=600)return;	//超区域了
                break;
            }
        }
    }
}





void LCD_Draw_Circle(u16 x0,u16 y0,u8 r,struct fb_fix_screeninfo finfo, struct fb_var_screeninfo vinfo, char *fbp)
{
    int a,b;
    int di;
    a=0;b=r;
    di=3-(r<<1);             //判断下个点位置的标志
    while(a<=b)
    {
        LCD_DrawPoint(x0+a, y0-b, finfo, vinfo, fbp);
        LCD_DrawPoint(x0+b, y0-a, finfo, vinfo, fbp);
        LCD_DrawPoint(x0+b, y0+a, finfo, vinfo, fbp);
        LCD_DrawPoint(x0+a, y0+b, finfo, vinfo, fbp);
        LCD_DrawPoint(x0-a, y0+b, finfo, vinfo, fbp);
        LCD_DrawPoint(x0-b, y0+a, finfo, vinfo, fbp);
        LCD_DrawPoint(x0-a, y0-b, finfo, vinfo, fbp);
        LCD_DrawPoint(x0-b, y0-a, finfo, vinfo, fbp);
        a++;
        //使用Bresenham算法画圆
        if(di<0)di +=4*a+6;
        else
        {
            di+=10+4*(a-b);
            b--;
        }
    }
}


void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p,struct fb_fix_screeninfo finfo, struct fb_var_screeninfo vinfo, char *fbp)
{
    u8 x0=x;
    width+=x;
    height+=y;
    while((*p<='~')&&(*p>=' '))//判断是不是非法字符!
    {
        if(x>=width){x=x0;y+=size;}
        if(y>=height)break;//退出
        LCD_ShowChar(x, y, *p ,size,finfo, vinfo, fbp);
        x+=size/2;
        p++;
    }
}

#endif 