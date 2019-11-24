#include "widget.h"
#include "ui_widget.h"


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
#include "GeoTrans.h"
#include "PointOr.h"
#include "MathOr.h"
#include "BasicGui.h"
#include "RGB2HSL.h"
#include "ColorDec.h"
#include "Piclib.h"

#ifdef __cplusplus
}
#endif


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    Mat_Init;
    Mat src1 = Load("E:\\QTProject\\LITECV\\picture\\lena.png");
    Mat src2 = Load("E:\\QTProject\\LITECV\\picture\\lena.jpg");
    save("E:\\QTProject\\LITECV\\picture\\test.bmp",&src1);
    save("E:\\QTProject\\LITECV\\picture\\test1.bmp",&src2);
    QImage img = QImage((const unsigned char*)(src2.imgData),
                        src2.width, src2.highth, QImage::Format_RGB888);
    //设定图像大小自适应label窗口的大小
    img = img.scaled(ui->label->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->label->setPixmap(QPixmap::fromImage(img));

}

Widget::~Widget()
{
    delete ui;
}

