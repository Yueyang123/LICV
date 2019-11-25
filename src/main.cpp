#include "Linwin.h"
#include "camera.h"
#include <QApplication>


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Linwin w("F://LiteCV//LITECV//picture//test.bmp");
    MyCameraDialog q;
    w.show();
    q.show();


    return a.exec();
}

