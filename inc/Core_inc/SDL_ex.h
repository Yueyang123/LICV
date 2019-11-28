#ifndef SDL_EX_H
#define SDL_EX_H


#include "cv.h"
#include "SDL.h"
#include "Mat.h"
#include "stdio.h"

void put_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
void draw_point(SDL_Surface *screen,POINT p,Uint32 color);

static inline SDL_Wait()
{
    	SDL_Event windowEvent;
		while(true) {
			if (SDL_PollEvent(&windowEvent)) {
				if (SDL_QUIT == windowEvent.type) {
					break;
				}
			}
		}
}


#endif // DEBUG