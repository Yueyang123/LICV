#include "widget.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w("E:\\QTProject\\LITECV\\picture\\lena.png");
    w.show();

    return a.exec();
}

