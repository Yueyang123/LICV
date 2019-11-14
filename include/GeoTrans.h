/*************************************************
Copyright © Yueyang Co. Ltd. 2019-2029. All rights reserved.
File name: GeoTrans.h
Author： Yueyang
Version: V1.0
Description: 提供对于图片的几何变换
Others: 
Log: 11.3 Yueyang
*************************************************/

Mat imrotate(Mat bmpImg,int Angle);

Mat immove(Mat mat,int dir,int distance);

Mat creatMapMat(Mat src,  int rows_c, int cols_c,double startdealta);

