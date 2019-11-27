#-------------------------------------------------
#
# Project created by QtCreator 2019-11-22T12:02:31
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia

QT       += multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LITECV
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    src/Core/arm_linux_hardpatch.c \
    src/Core/BasicGui.c \
    src/Core/bmp.c \
    src/Core/ColorDec.c \
    src/Core/GeoTrans.c \
    src/Core/Mat.c \
    src/Core/MathOr.c \
    src/Core/Piclib.c \
    src/Core/PointOr.c \
    src/Core/RGB2HSL.c \
    src/main.cpp \
    Qt/Qwin/Linwin.cpp \
    Qt/Camera/camera.cpp



INCLUDEPATH +=  \
              inc  \
              inc/Qt_inc  \
              inc/Piclib_inc   \
              inc/Core_inc

HEADERS += \
    inc/Core_inc/arm_linux_hardpatch.h \
    inc/Core_inc/BasicGui.h \
    inc/Core_inc/ColorDec.h \
    inc/Core_inc/cv.h \
    inc/Core_inc/font.h \
    inc/Core_inc/GeoTrans.h \
    inc/Core_inc/Mat.h \
    inc/Core_inc/MathOr.h \
    inc/Core_inc/PointOr.h \
    inc/Piclib_inc/bmp.h \
    inc/Piclib_inc/inffast.h \
    inc/Piclib_inc/inffixed.h \
    inc/Piclib_inc/inflate.h \
    inc/Piclib_inc/inftrees.h \
    inc/Piclib_inc/jconfig.h \
    inc/Piclib_inc/jerror.h \
    inc/Piclib_inc/jmorecfg.h \
    inc/Piclib_inc/jpeglib.h \
    inc/Piclib_inc/Piclib.h \
    inc/Piclib_inc/png.h \
    inc/Piclib_inc/pngconf.h \
    inc/Piclib_inc/pngdebug.h \
    inc/Piclib_inc/pnginfo.h \
    inc/Piclib_inc/pnglibconf.h \
    inc/Piclib_inc/pngpriv.h \
    inc/Piclib_inc/pngstruct.h \
    inc/Piclib_inc/RGB2HSL.h \
    inc/Piclib_inc/trees.h \
    inc/Piclib_inc/turbojpeg.h \
    inc/Piclib_inc/zconf.h \
    inc/Piclib_inc/zlib.h \
    inc/Piclib_inc/zutil.h \
    inc/Qt_inc/camera.h \
    inc/Qt_inc/Linwin.h

LIBS        +=F:\LITECV\LiteCV\lib\lib*

FORMS += \
    Qt/Qwin/Linwin.ui
