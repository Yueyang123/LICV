#include "SDL_ex.h"

/*
 * Return the pixel value at (x, y) 获取像素
 * NOTE: The surface must be locked before calling this!
 */
Uint32 get_pixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
 
    switch(bpp) {
    case 1:
        return *p;
 
    case 2:
        return *(Uint16 *)p;
 
    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
 
    case 4:
        return *(Uint32 *)p;
 
    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}
 
/*
 * Set the pixel at (x, y) to the given value 设置像素
 * NOTE: The surface must be locked before calling this!
 */
void put_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    switch (surface->format->BytesPerPixel)
  	{
    	case 1: // Assuming 8-bpp
    	{
      		Uint8 *bufp;
      		bufp = (Uint8 *)surface->pixels + y*surface->pitch + x;
      		*bufp = pixel;
    	}
    	break;
    	case 2: // Probably 15-bpp or 16-bpp
    	{
      		Uint16 *bufp;
      		bufp = (Uint16 *)surface->pixels + y*surface->pitch/2 + x;
      		*bufp = pixel;
    	}
    	break;
    	case 3: // Slow 24-bpp mode, usually not used
    	{
      		Uint8 *bufp;
      		bufp = (Uint8 *)surface->pixels + y*surface->pitch + x * 3;
      		if(SDL_BYTEORDER == SDL_LIL_ENDIAN)
      		{
        		bufp[0] = pixel;
        		bufp[1] = pixel >> 8;
        		bufp[2] = pixel >> 16;
      		} else {
        		bufp[2] = pixel;
        		bufp[1] = pixel >> 8;
        		bufp[0] = pixel >> 16;
      		}
    	}
    	break;
    	case 4: // Probably 32-bpp
    	{
      		Uint32 *bufp;
      		bufp = (Uint32 *)surface->pixels + y*surface->pitch/4 + x;
      		*bufp = pixel;
    	}
    	break;
  	}
}
 
 
/**
 * draw point 画点
 */
void draw_point(SDL_Surface *screen,POINT p,Uint32 color)
{
	int x,y;
	//x = p.x-m_FaceInfo.headArea.left-1;
	//y = p.y-m_FaceInfo.headArea.top-1;
	x = p.x;
	y = p.y;
    if ( SDL_MUSTLOCK(screen) ) {
        if ( SDL_LockSurface(screen) < 0 ) {
            printf("Can't lock screen: %s\n", SDL_GetError());
            return;
        }
    }
 
	put_pixel(screen, x, y, color);
 
    if ( SDL_MUSTLOCK(screen) ) {
        SDL_UnlockSurface(screen);
    }
    /* Update just the part of the display that we've changed */
    // SDL_UpdateRect(screen, x,y, 1, 1);
 
    return;
 
}
 

/**
 * draw line 画bresenham线
 */
void bresenham_line(SDL_Surface *screen,int x1,int y1,int x2, int y2, Uint32 c)
{
	int dx,dy,x,y,p,const1,const2,inc,tmp;
	dx = x2-x1;
	dy = y2-y1;
	if(dx*dy >= 0)
		inc = 1;
	else
		inc = -1;
	if(abs(dx)>abs(dy))
	{
		if(dx<0)
		{
			tmp = x1;
			x1 = x2;
			x2 = tmp;
			tmp = y1;
			y1 = y2;
			y2 = tmp;
			dx = -dx;
			dy = -dy;
		}
		p = 2*dy-dx;
		const1 = 2*dy;
		const2 = 2*(dy-dx);
		x = x1;
		y = y1;
		put_pixel(screen,x,y,c);
		while(x<x2)
		{
			x++;
			if(p<0)
				p += const1;
			else
			{
				y += inc;
				p += const2;
			}
			put_pixel(screen,x,y,c);
		}
	}
	else
	{
		if(dy<0)
		{
			tmp = x1;
			x1 = x2;
			x2 = tmp;
			tmp = y1;
			y1 = y2;
			y2 = tmp;
			dx = -dx;
			dy = -dy;
		}
		p = 2*dy-dx;
		const1 = 2*dy;
		const2 = 2*(dy-dx);
		x = x1;
		y = y1;
		put_pixel(screen,x,y,c);
		while(y<y2)
		{
			y++;
			if(p<0)
				p += const1;
			else
			{
				x+=inc;
				p+=const2;
			}
			put_pixel(screen,x,y,c);
		}
	}
}
 
/**
 * dda_line 画线
 * 
 * screen 屏幕指针
 * xa     开始点X
 * ya     开始点Y
 * xb     结束点X
 * yb     结束点Y
 * c      颜色
 */
void dda_line(SDL_Surface *screen,int xa,int ya,int xb,int yb,Uint32 c)
{
	float delta_x,delta_y,x,y;
	int dx,dy,steps,k;
	dx = xb-xa;
	dy = yb-ya;
 
	if(abs(dx)>abs(dy))
		steps = abs(dx);
	else
		steps = abs(dy);
 
	delta_x = (float)dx/(float)steps;
	delta_y = (float)dy/(float)steps;
	x = xa;
	y = ya;
	put_pixel(screen,x,y,c);
	for(k = 0;k<steps;k++)
	{
		x+=delta_x;
		y+=delta_y;
		put_pixel(screen,x,y,c);
	}
	return ;
}
 
 
/**
 * 画圆调用子方法
 * 
 */
void plot_circle_points(SDL_Surface *screen,int xc,int yc,int x,int y,Uint32 c)
{
	put_pixel(screen,xc+x,yc+y,c);
	put_pixel(screen,xc-x,yc+y,c);
	put_pixel(screen,xc+x,yc-y,c);
	put_pixel(screen,xc-x,yc-y,c);
	put_pixel(screen,xc+y,yc+x,c);
	put_pixel(screen,xc-y,yc+x,c);
	put_pixel(screen,xc+y,yc-x,c);
	put_pixel(screen,xc-y,yc-x,c);
}
 
/**
 * 画圆
 *
 * screen 屏
 * cp     圆中心点
 * radius 半径
 * c      颜色
 */
void bresenham_circle(SDL_Surface *screen,POINT cp,int radius,Uint32 c)
{
	int xc, yc;
	int x,y,p;
	//xc = cp.x - m_FaceInfo.headArea.left-1;
	//yc = cp.y - m_FaceInfo.headArea.top-1;
	xc = cp.x;
	yc = cp.y;
	x = 0;
	y = radius;
	p = 3-2*radius;
	while(x<y)
	{
		plot_circle_points(screen,xc,yc,x,y,c);
		if(p<0)
			p=p+4*x+6;
		else
		{
			p=p+4*(x-y)+10;
			y-=1;
		}
		x+=1;
	}
	if(x == y)
	plot_circle_points(screen,xc,yc,x,y,c);
}
