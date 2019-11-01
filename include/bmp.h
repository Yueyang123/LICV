/*
*��Ȩ���� (C)2019,Yueyang.
*�ļ����ƣ�bmp.h
*����ժҪ��LiteCV bmpͼƬ��������
*��ǰ�汾��V1.0
*���ߣ���Խ
*������ڣ�20191020
*/

#ifndef BMP_H_INCLUDED
#define BMP_H_INCLUDED
#include "stdio.h"
#include "Mat.h"


 int    (*filewrite)(const void *  _Str,int _Size,int _Count,FILE *  _File);
 int    (*fileread)(void * _DstBuf,int _ElementSize,int _Count,FILE * _File);
 FILE * (*fileopen)(const char *  _Filename,const char *  _Mode) ;
 int    (*fileseek)(FILE *_File,long _Offset,int _Origin);
 int    (*fileclose)(FILE *_File);
 void   (*Li_free)(void *_Memory);
 void * (*Li_malloc)(size_t _Size);
 void * (*Li_memcpy)(void * _Dst,const void * _Src,size_t _Size);
 void   (*show)(Mat* mat);
 u8*    (*at)(Mat* mat,int width,int highth);
 int    (*process)(Mat* mat,int x,int y,u32 color);
 Mat    (*load)(char *filepath);
 int    (*save)(char *filepath,Mat* mat);
 Mat    (*copy)(Mat mat);
 void   (*destory)(Mat* mat);

//���·���Ƿ�Ϸ����ļ��ܴ򿪣���bmpΪ��׺��
int CheckbmpFilePath(char *filepath);
//����λͼ���ļ�ͷ
int ReadbmpFileHeader(char *filepath,BITMAPFILEHEADER *bmfh);
//��ӡλͼ���ļ�ͷ
void PrintbmpFileHeader(BITMAPFILEHEADER *bmfh);
//����λͼ����Ϣͷ
int ReadbmpInfoHeader(char *filepath,BITMAPINFOHEADER *bmih);
//��ӡλͼ����Ϣͷ
void PrintbmpInfoHeader(BITMAPINFOHEADER *bmih);
//����λͼ����������
int ReadbmpPixelData(char *filepath,BYTE *imgData);
//����ÿ��������ռ���ֽ���
LONG GetLineBytes(int imgWidth,int bitCount);
//��ӡλͼ����������
void PrintbmpPixelData(BYTE *imgData,int width,int height,int bitCount);
//���Ϊλͼ
int SaveAsbmpImage(char *filepath,Mat* mat);
//��ʾλͼ
void ShowbmpImage(Mat* mat);
//bmp�ļ��Ķ�ȡ����뺯��
Mat bmpload(char *filepath);
//BMPͼƬ���������ص�
int bmpprocess(Mat* mat,int width,int highth,u32 color);
//BMP���ص�Ѱַ����
u8* bmpat(Mat* mat,int width,int highth);

Mat bmpcopy(Mat mat);

void bmpdestory(Mat* mat);

#endif // BMP_H_INCLUDED







