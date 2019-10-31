#ifndef BMP_H_INCLUDED
#define BMP_H_INCLUDED

#include "cv.h"
#include "Mat.h"


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


#endif // BMP_H_INCLUDED







