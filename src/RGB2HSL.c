/*************************************************
Copyright © Yueyang Co. Ltd. 2019-2029. All rights reserved.
File name:PointOr.c
Author： Yueyang
Version: V1.0
Description: 提供图片HSL与RGB的互相转化算法
Others: 
Log: 11.13 Yueyang
*************************************************/

#include "RGB2HSL.h"

double MAX(double a,double b) 
{
    return   (a > b) ? a : b;
}
double MIN(double a,double b) 
{
    return  (a <b) ? a : b;
}
void RGB2HSV( u16 * h, u16 * s, u16 * v, u8 r, u8 g, u8 b)
{
    double rr, gg, bb;
    double hh, ss, vv;
    double cmax, cmin, cdes;

    rr = r;
    gg = g;
    bb = b;

    cmax = (rr > gg) ? rr : gg;
    if (bb > cmax) {
        cmax = bb;
    }

    cmin = (rr < gg) ? rr : gg;
    if (bb < cmin) {
        cmin = bb;
    }

    cdes = cmax - cmin;
    vv = cmax;

    if (cdes != 0) {
        ss = cdes * 60 / cmax;
        if (cmax == rr) {
            hh = (gg - bb) * 60 / cdes;
        }else if (cmax == gg) {
            hh = (bb - rr) * 60 / cdes + 2 * 60;
        }else {
            hh = (rr - gg) * 60 / cdes + 4 * 60;
        }
    }else if (cmax != 0) {
        ss = cdes * 60 / cmax;
        hh = 0;
    }else {
        ss = 0;
        hh = 0;
    }
    if (hh < 0) {
        hh += 6 * 60;
    }

    *h = hh * 1;
    *s = ss * 1;
    *v = vv * 1;
}

void HSV2RGB( u8 *r, u8 *g, u8 *b, u16 h, u16 s, u16 v)
{
    double rr = 0, gg = 0, bb = 0;
    double hh, ss, vv;

    if (h == 6 * 1 * 60) {
        h = 0;
    }
    hh = (double)h / 1;
    ss = (double)s / 1;
    vv = (double)v / 1;

    switch((int)(hh / 60)) {
        case 0:
            rr = 60;
            gg = hh;
            bb = 0;
            break;
        case 1:
            rr = 2 * 60 - hh;
            gg = 60;
            bb = 0;
            break;
        case 2:
            rr = 0;
            gg = 60;
            bb = hh - 2 * 60;
            break;
        case 3:
            rr = 0;
            gg = 4 * 60 - hh;
            bb = 60;
            break;
        case 4:
            rr = hh - 4 * 60;
            gg = 0;
            bb = 60;
            break;
        case 5:
            rr = 60;
            gg = 0;
            bb = 6 * 60 - hh;
            break;
    }

    rr = (rr + (60 - rr) * (60 - ss) / 60) * vv / 60;
    gg = (gg + (60 - gg) * (60 - ss) / 60) * vv / 60;
    bb = (bb + (60 - bb) * (60 - ss) / 60) * vv / 60;

    *r = rr;
    *g = gg;
    *b = bb;
    if (*r > 255)*r = 255;
    if (*g > 255)*g = 255;
    if (*b > 255)*b = 255;
}

void RGB2HLS( double *h, double *l, double *s, u8 r, u8 g, u8 b)
{
    double dr = (double)r/255;
    double dg = (double)g/255;
    double db = (double)b/255;
    double cmax = MAX(dr, MAX(dg, db));
    double cmin = MIN(dr, MIN(dg, db));
    double cdes = cmax - cmin;
    double hh, ll, ss;

    ll = (cmax+cmin)/2;
    if(cdes!=0){
        if(ll <= 0.5)
            ss = (cmax-cmin)/(cmax+cmin);
        else
            ss = (cmax-cmin)/(2-cmax-cmin);

        if(cmax == dr)
            hh = (0+(dg-db)/cdes)*60;
        else if(cmax == dg)
            hh = (2+(db-dr)/cdes)*60;
        else// if(cmax == b)
            hh = (4+(dr-dg)/cdes)*60;
        if(hh<0)
            hh+=360;
    }else
        hh = ss = 0;

    *h = hh;
    *l = ll;
    *s = ss;
}

/**
 * @fn      u8* GetHSL(Mat src)
 *
 * @brief   将一副图像转化为HSL数值
 *
 * @author  Yueyang
 * @date    2019/11/15
 *
 * @param   src   The picture type as the background
 * 
 * @return  HSL数组
 */
double* GetHSL(Mat src)
{
    int x,y;
    u8 *inaddr;
    u32 temp;
    double* outaddr=malloc(3*src.highth*src.width*sizeof(double));

    for(y=0;y<src.width;y++)
    for(x=0;x<src.highth;x++)
    {
    inaddr=at(&src,x,y);
    temp=3*src.width*y+3*x;
    RGB2HLS(outaddr+temp,outaddr+temp+2,outaddr+temp+1,*(inaddr+2),*(inaddr+1),*(inaddr));
    }
    return outaddr;
}