#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>
#include <process.h>
#include "bmp.h"
#include "cv.h"


int main()
{
   Mat src;
   int i,j;
   u8* addr;
   src=bmpload("F:\\myproject\\LiteCV\\picture\\lena.bmp");
   // PrintbmpInfoHeader(&src->bmi);
   // printf("%s",src->PATH);

   for(j=0;j<=511;j++)
      {
        *(bmpat(&src,j,j)+1)=0x0F;
      }
   SaveAsbmpImage("F:\\myproject\\LiteCV\\picture\\lena0.bmp",&src);
   ShowbmpImage(&src);
}

 