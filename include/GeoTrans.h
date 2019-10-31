/*
*版权所有 (C)2019,Yueyang.
*文件名称：main.c
*内容摘要：LiteCV几何变换
*当前版本：V1.0
*作者：杨越
*完成日期：20191020
*/


Mat imrotate(Mat bmpImg,int Angle);
//DIR:0左 1右 2上  3 下
Mat immove(Mat mat,int dir,int distance);