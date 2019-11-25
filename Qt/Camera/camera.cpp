#include "Camera.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
 
MyCameraDialog::MyCameraDialog(QWidget *parent)
    : QDialog(parent)
{
    this->setFixedSize(800, 600);
 
    camera = new QCamera();
    cameraViewFinder = new QCameraViewfinder();
    cameraImageCapture = new QCameraImageCapture(camera);
 
    captureBtn = new QPushButton();
    saveBtn = new QPushButton();
    exitBtn = new QPushButton();
 
    displayLabel = new QLabel();
    displayLabel->setFixedSize(160, 120);
    displayLabel->setScaledContents(true);
 
    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addWidget(displayLabel);
    rightLayout->addStretch();
    rightLayout->addWidget(captureBtn);
    rightLayout->addWidget(saveBtn);
    rightLayout->addWidget(exitBtn);
 
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(cameraViewFinder);
    mainLayout->addLayout(rightLayout);
 
    connect(captureBtn, SIGNAL(clicked()), this, SLOT(captureBtnResponded()));
    connect(saveBtn, SIGNAL(clicked()), this, SLOT(saveBtnResponded()));
    connect(exitBtn, SIGNAL(clicked()), this, SLOT(exitBtnResponded()));
    connect(cameraImageCapture, SIGNAL(imageCaptured(int,QImage)), this, SLOT(cameraImageCaptured(int,QImage)));
 
    cameraImageCapture->setCaptureDestination(QCameraImageCapture::CaptureToFile);
    camera->setCaptureMode(QCamera::CaptureStillImage);
    camera->setViewfinder(cameraViewFinder);
    camera->start();
 
    this->setLayout(mainLayout);
    this->translateLanguage();
 
}
 
MyCameraDialog::~MyCameraDialog()
{
 
}
 
void MyCameraDialog::translateLanguage()
{
    this->setWindowTitle(tr("testCapture"));
    captureBtn->setText(tr("capture"));
    saveBtn->setText(tr("save"));
    exitBtn->setText(tr("exit"));
}
 
void MyCameraDialog::captureBtnResponded()
{
    cameraImageCapture->capture();
}
 
void MyCameraDialog::saveBtnResponded()
{
    const QPixmap *pixmap = displayLabel->pixmap();
    if(pixmap) {pixmap->save("F://LiteCV//LITECV//picture//test.bmp");}
}
 
void MyCameraDialog::exitBtnResponded()
{
    camera->stop();
    this->close();
}
 
void MyCameraDialog::cameraImageCaptured(int id, QImage image)
{
    displayLabel->setPixmap(QPixmap::fromImage(image));
}
