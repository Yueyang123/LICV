#ifndef RGB2HSL_H
#define RGB2HSL_H

#include "cv.h"
#include "Mat.h"
#include <stdio.h>
#include <stdlib.h>

double* GetHSL(Mat src);
void RGB2HLS( double *h, double *l, double *s, u8 r, u8 g, u8 b);

#endif