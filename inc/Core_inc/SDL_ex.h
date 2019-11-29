#ifndef SDL_EX_H
#define SDL_EX_H


#include "cv.h"
#include "SDL.h"
#include "Mat.h"
#include "stdio.h"

void put_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
void draw_point(SDL_Surface *screen,POINT p,Uint32 color);

static inline int SDL_Wait(SDL_Window*win)
{
    	SDL_Event windowEvent;
		while(true) {
			if (SDL_PollEvent(&windowEvent)) {
				if (SDL_QUIT == windowEvent.type) {
					SDL_DestroyWindow(win);
				    SDL_Quit();
					break;
				}
			}
		}
		return 0;
}


#endif // DEBUG