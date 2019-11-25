﻿#include "widget.h"
#include "ui_widget.h"
#include <string>

#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "bmp.h"
#include "cv.h"
#include "Mat.h"
#include "Piclib.h"
#include "GeoTrans.h"
#ifdef __cplusplus
}
#endif

using namespace  std;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

}

Widget::Widget(char* filepath,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    BYTE* inaddr, *outaddr;
    ui->setupUi(this);
    Mat_Init;
    string path="E:\\QTProject\\LITECV\\picture\\test.bmp";
    Mat src1 = Load((char*)path.data(),filepath);
    BYTE* temp=new BYTE[3*src1.width*src1.highth];
    //BGR转RGB存储
    for(int x=0;x<src1.width;x++)
        for(int y=0;y<src1.highth;y++)
        {
            inaddr=temp+3*src1.width*y+3*x;
            outaddr=(BYTE*)src1.imgData+3*src1.width*y+3*x;
            *inaddr=*(outaddr+2);
            *(inaddr+1)=*(outaddr+1);
            *(inaddr+2)=*(outaddr);
        }

    QImage img = QImage((const unsigned char*)(temp),
                        src1.width, src1.highth, QImage::Format_RGB888);
    //设定图像大小自适应label窗口的大小
    img = img.scaled(ui->label->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    delete []temp;
    ui->label->setPixmap(QPixmap::fromImage(img));

}


Widget::~Widget()
{
    delete ui;
}

