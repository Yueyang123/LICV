#ifndef PIC_H
#define PIC_H

#include "jpeglib.h"
#include "Mat.h"

GLOBAL(void)
write_JPEG_file(char *filename, int quality,JSAMPLE *image_buffer,int image_height,int image_width);


Mat read_JPEG_file(char* dstname,char *filename);

Mat readpng(char* dstname,char* filename);

#endif