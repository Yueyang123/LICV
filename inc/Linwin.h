#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Linwin;
}

class Linwin : public QWidget
{
    Q_OBJECT

public:
    Linwin(char* filepath,QWidget *parent = 0);
    ~Linwin();

private:
    Ui::Linwin *ui;
};

#endif // WIDGET_H
