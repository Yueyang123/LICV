/*
*��Ȩ���� (C)2019,Yueyang.
*�ļ����ƣ�Mat.c
*����ժҪ��LiteCV������������Matʵ��
*��ǰ�汾��V1.0
*���ߣ���Խ
*������ڣ�20191020
*/

#include "bmp.h"


void Mat_INIT()
{
    show=ShowbmpImage;
    at=bmpat;
    process=bmpprocess;
    load=bmpload;
    save=SaveAsbmpImage;
    copy=bmpcopy;
}



