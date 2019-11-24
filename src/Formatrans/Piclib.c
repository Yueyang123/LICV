/*************************************************
Copyright © Yueyang Co. Ltd. 2019-2029. All rights reserved.
File name: Piclib.c
Author： Yueyang
Version: V1.0
Description: LiteCV 除了bmp以外的其他图片的的有关扩展
Others: jpeg  png
依赖于libjpeg libpng 
Log: 11.21 Yueyang
*************************************************/


#include <malloc.h>
#include "string.h"
/*
 * Include file for users of JPEG library.
 * You will need to have included system headers that define at least
 * the typedefs FILE and size_t before you can include jpeglib.h.
 * (stdio.h is sufficient on ANSI-conforming systems.)
 * You may also wish to include "jerror.h".
 */
#include "jconfig.h"
#include "jmorecfg.h"
#include <jpeglib.h>
#include "png.h"
#include "pngstruct.h"
#include <stdio.h>
#include <stdlib.h>
#include "Mat.h"
/*
 * <setjmp.h> is used for the optional error recovery mechanism shown in
 * the second part of the example.
 */

#include <setjmp.h>


// extern JSAMPLE *image_buffer;   /* Points to large array of R,G,B-order data */
// extern int image_height;        /* Number of rows in image */
// extern int image_width;         /* Number of columns in image */


void write_JPEG_file(char *filename, int quality,JSAMPLE *image_buffer,int image_height,int image_width)
{
  struct jpeg_compress_struct cinfo;
  struct jpeg_error_mgr jerr;
  /* More stuff */
  FILE *outfile;                /* target file */
  JSAMPROW row_pointer[1];      /* pointer to JSAMPLE row[s] */
  int row_stride;               /* physical row width in image buffer */

  cinfo.err = jpeg_std_error(&jerr);
  /* Now we can initialize the JPEG compression object. */
  jpeg_create_compress(&cinfo);

  if ((outfile = fopen(filename, "wb")) == NULL) {
    fprintf(stderr, "can't open %s\n", filename);
  }
  jpeg_stdio_dest(&cinfo, outfile);

  cinfo.image_width = image_width;      /* image width and height, in pixels */
  cinfo.image_height = image_height;
  cinfo.input_components = 3;           /* # of color components per pixel */
  cinfo.in_color_space = JCS_RGB;       /* colorspace of input image */

  jpeg_set_defaults(&cinfo);

  jpeg_set_quality(&cinfo, quality, TRUE /* limit to baseline-JPEG values */);

  jpeg_start_compress(&cinfo, TRUE);

  row_stride = image_width * 3; /* JSAMPLEs per row in image_buffer */

  while (cinfo.next_scanline < cinfo.image_height) {
    row_pointer[0] = &image_buffer[cinfo.next_scanline * row_stride];
    (void)jpeg_write_scanlines(&cinfo, row_pointer, 1);
  }


  jpeg_finish_compress(&cinfo);
  /* After finish_compress, we can close the output file. */
  fclose(outfile);
  jpeg_destroy_compress(&cinfo);
}


struct my_error_mgr {
  struct jpeg_error_mgr pub;    /* "public" fields */

  jmp_buf setjmp_buffer;        /* for return to caller */
};

typedef struct my_error_mgr *my_error_ptr;

/*
 * Here's the routine that will replace the standard error_exit method:
 */

METHODDEF(void)
my_error_exit(j_common_ptr cinfo)
{
  /* cinfo->err really points to a my_error_mgr struct, so coerce pointer */
  my_error_ptr myerr = (my_error_ptr)cinfo->err;

  /* Always display the message. */
  /* We could postpone this until after returning, if we chose. */
  (*cinfo->err->output_message) (cinfo);

  /* Return control to the setjmp point */
  longjmp(myerr->setjmp_buffer, 1);
}


u8* analyse_jpeg(char *filename)
{
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    JSAMPARRAY buffer;
    unsigned char *src_buff;
    unsigned char *point;
    FILE *infile;                 /* source file */

    if ((infile = fopen(filename, "rb")) == NULL) {
    fprintf(stderr, "can't open %s\n", filename);
   }
    cinfo.err=jpeg_std_error(&jerr);    //一下为libjpeg函数，具体参看相关文档
    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo,infile);
    jpeg_read_header(&cinfo,TRUE);
    jpeg_start_decompress(&cinfo);

    unsigned long width=cinfo.output_width;
    unsigned long height=cinfo.output_height;
    unsigned short depth=cinfo.output_components;

    src_buff=malloc(width*height*depth);
    memset(src_buff,0,sizeof(unsigned char)*width*height*depth);

    buffer=(*cinfo.mem->alloc_sarray)
        ((j_common_ptr)&cinfo,JPOOL_IMAGE,width*depth,1);

    point=src_buff;
    while (cinfo.output_scanline<height)
    {
        jpeg_read_scanlines(&cinfo,buffer,1);    //读取一行jpg图像数据到buffer
        memcpy(point,*buffer,width*depth);    //将buffer中的数据逐行给src_buff
        point+=width*depth;            //一次改变一行
    }

    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    return src_buff;
}

/*
 * Sample routine for JPEG decompression.  We assume that the source file name
 * is passed in.  We want to return 1 on success, 0 on error.
 */


Mat
read_JPEG_file(char* dstname,char *filename)
{
   
  /* This struct contains the JPEG decompression parameters and pointers to
   * working space (which is allocated as needed by the JPEG library).
   */
  struct jpeg_decompress_struct cinfo;
  /* We use our private extension JPEG error handler.
   * Note that this struct must live as long as the main JPEG parameter
   * struct, to avoid dangling-pointer problems.
   */
  struct my_error_mgr jerr;
  /* More stuff */
  FILE *infile;                 /* source file */
  JSAMPARRAY buffer;            /* Output row buffer */
  int row_stride;               /* physical row width in output buffer */

  /* In this example we want to open the input file before doing anything else,
   * so that the setjmp() error recovery below can assume the file is open.
   * VERY IMPORTANT: use "b" option to fopen() if you are on a machine that
   * requires it in order to read binary files.
   */

  if ((infile = fopen(filename, "rb")) == NULL) {
    fprintf(stderr, "can't open %s\n", filename);
  }

  /* Step 1: allocate and initialize JPEG decompression object */

  /* We set up the normal JPEG error routines, then override error_exit. */
  cinfo.err = jpeg_std_error(&jerr.pub);
  jerr.pub.error_exit = my_error_exit;
  /* Establish the setjmp return context for my_error_exit to use. */
  if (setjmp(jerr.setjmp_buffer)) {
    /* If we get here, the JPEG code has signaled an error.
     * We need to clean up the JPEG object, close the input file, and return.
     */
    printf("ERROR");
    jpeg_destroy_decompress(&cinfo);
    fclose(infile);
  }
  /* Now we can initialize the JPEG decompression object. */
  jpeg_create_decompress(&cinfo);

  /* Step 2: specify data source (eg, a file) */

  jpeg_stdio_src(&cinfo, infile);

  /* Step 3: read file parameters with jpeg_read_header() */

  jpeg_read_header(&cinfo, TRUE);


  jpeg_start_decompress(&cinfo);
  row_stride = cinfo.output_width * cinfo.output_components;
  /* Make a one-row-high sample array that will go away when done with image */
  buffer =malloc(row_stride*1);
 

   Mat dst=Create(dstname,cinfo.output_width,cinfo.output_height,3);
   u32 temp=0;

   while (cinfo.output_scanline < cinfo.output_height) {
     jpeg_read_scanlines(&cinfo, &buffer,1);
     memcpy((dst.imgData+temp*row_stride), buffer,row_stride);
     temp++;
  }
    free(buffer);
  /* Step 7: Finish decompression */

  (void)jpeg_finish_decompress(&cinfo);
  /* We can ignore the return value since suspension is not possible
   * with the stdio data source.
   */

  /* Step 8: Release JPEG decompression object */

  /* This is an important step since it will release a good deal of memory. */
  jpeg_destroy_decompress(&cinfo);

  /* After finish_decompress, we can close the input file.
   * Here we postpone it until after no more JPEG errors are possible,
   * so as to simplify the setjmp error logic above.  (Actually, I don't
   * think that jpeg_destroy can do an error exit, but why assume anything...)
   */
  fclose(infile);

  /* At this point you may want to check to see whether any corrupt-data
   * warnings occurred (test whether jerr.pub.num_warnings is nonzero).
   */

  /* And we're done! */
  return dst;
}




Mat read_PNG_file(char* dstname,char* filename)
{

// 前边几句是扯淡，初始化各种结构

FILE* file = fopen(filename, "rb");

png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);

png_infop info_ptr = png_create_info_struct(png_ptr);

setjmp(png_jmpbuf(png_ptr));

// 这句很重要

png_init_io(png_ptr, file);

// 读文件了

png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_EXPAND, 0);

// 得到文件的宽高色深

int m_width = png_get_image_width(png_ptr, info_ptr);
int m_height = png_get_image_height(png_ptr, info_ptr);
Mat dst=Create(dstname,m_width,m_height,3);
int color_type = png_get_color_type(png_ptr, info_ptr);

int size = m_height * m_width * 3;

int pos = 0;

// row_pointers里边就是传说中的rgba数据了

png_bytep* row_pointers = png_get_rows(png_ptr, info_ptr);

// 拷贝！！注意，如果你读取的png没有A通道，就要3位3位的读。还有就是注意字节对其的问题，最简单的就是别用不能被4整除的宽度就行了。读过你实在想用，就要在这里加上相关的对齐处理。

for(int i = 0; i < m_height; i++)
{
   for(int j = 0; j < (4 * m_width); j += 4)
   {
    dst.imgData[pos++] = row_pointers[i][j + 2]; // blue
    dst.imgData[pos++] = row_pointers[i][j + 1]; // green
    dst.imgData[pos++] = row_pointers[i][j];   // red
    // bgra[pos++] = row_pointers[i][j + 3]; // alpha
   }
}
// 好了，你可以用这个数据作任何的事情了。。。把它显示出来或者打印出来都行。



png_destroy_read_struct(&png_ptr, &info_ptr, 0);

fclose(file);

return dst;

}
