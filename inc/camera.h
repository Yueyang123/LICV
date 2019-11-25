

#ifndef MYCAMERADIALOG_H
#define MYCAMERADIALOG_H
 
#include <QDialog>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
 
#include <QLabel>
#include <QPushButton>
 
class MyCameraDialog : public QDialog
{
    Q_OBJECT
 
public:
    MyCameraDialog(QWidget *parent = 0);
    ~MyCameraDialog();
 
private slots:
    void captureBtnResponded();
    void saveBtnResponded();
    void exitBtnResponded();
    void cameraImageCaptured(int id, QImage image);
 
private:
    // 系统摄像设备（摄像头）
    QCamera *camera;
    // 摄像取景器部件
    QCameraViewfinder *cameraViewFinder;
    // 截图部件
    QCameraImageCapture *cameraImageCapture;
 
    QPushButton *captureBtn;
    QPushButton *saveBtn;
    QPushButton *exitBtn;
 
    QLabel *displayLabel;
 
    void translateLanguage();
};
 
#endif // MYCAMERADIALOG_H
