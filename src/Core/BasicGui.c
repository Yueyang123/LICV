/*************************************************
Copyright © Yueyang Co. Ltd. 2019-2029. All rights reserved.
File name:BasicGui.c
Author： Yueyang
Version: V1.0
Description: 基础绘图
Others: 
Log: 11.8 Yueyang
*************************************************/

#include "BasicGui.h"
#include "font.h"

void DrawPoint(Mat* mat,u32 color,int x,int y)
{
    if(x>=0&&x<=mat->width&&y>0&&y<mat->highth)
    {
    u8* inaddr;
    inaddr=at(mat,x,y);
    *inaddr=(u8)((color&0x00FF0000)>>16);//B
    *(inaddr+1)=(u8)((color&0x0000FF00)>>8);//G
    *(inaddr+2)=(u8)(color&0x000000FF);//R
    }

}


void DrawLine(Mat* mat,u32 color,u16 x1, u16 y1, u16 x2, u16 y2)
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
        DrawPoint(mat,color,uRow, uCol);
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

void DrawCircle(Mat* mat ,u32 color,u16 x0,u16 y0,u8 r)
{
    int a,b;
    int di;
    a=0;b=r;
    di=3-(r<<1);             //判断下个点位置的标志
    while(a<=b)
    {
        DrawPoint(mat,color,x0+a, y0-b);
        DrawPoint(mat,color,x0+b, y0-a);
        DrawPoint(mat,color,x0+b, y0+a);
        DrawPoint(mat,color,x0+a, y0+b);
        DrawPoint(mat,color,x0-a, y0+b);
        DrawPoint(mat,color,x0-b, y0+a);
        DrawPoint(mat,color,x0-a, y0-b);
        DrawPoint(mat,color,x0-b, y0-a);
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


void ShowChar(Mat* mat,u32 color,u16 x,u16 y,u8 num,u8 size)
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
            if(temp&0x80)DrawPoint(mat,color,x,y);
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



void ShowString(Mat* mat,u32 color,u8*p,u16 x,u16 y,u16 width,u16 height,u8 size)
{
    u8 x0=x;
    width+=x;
    height+=y;
    while((*p<='~')&&(*p>=' '))//判断是不是非法字符!
    {
        if(x>=width){x=x0;y+=size;}
        if(y>=height)break;//退出
        ShowChar(mat,color,x, y, *p ,size);
        x+=size/2;
        p++;
    }
}


//在一副图片上简单的绘制一副灰度分布图
//需要绘制直方图的
//cols x轴对应的最大像素点
//rows y轴的最大像素点
//注意：1.请确保result已经完成内存申请！！！
//     2.确保cols/length>1
Mat DrawCDF(float* result,u32 length,u32 cols,u32 rows)
{
    float Max=0.0f;
    u8 tbuf[10];
    float Pos=(float)cols/length;//两直方图在图片中的间隔
    float y_fact;//使直方图在高度上适配的比例因子
    u32 i,x;
    Mat out=Create("..\\picture\\CDF.bmp",cols,rows,3);
    for(i=1;i<=length-1;i++)
    {
        if(*(result+i)>Max)
        {
            Max=*(result+i);
        }
    }
    y_fact=rows/Max;
    
    sprintf(tbuf,"%f",Max);
    ShowString(&out,GUI_BLUE,tbuf,0,0,100,16,16);
    i=0;
    for(x=0;x<cols;x+=2)
    {
     DrawLine(&out,GUI_RED,x,rows,x,rows-*(result+i)*y_fact);
     i++;
    }
    return out;
}
