#-------------------------------------------------
#
# Project created by QtCreator 2019-11-22T12:02:31
#
#-------------------------------------------------

QT       += core gui

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
        src/main.cpp \
        Qt/widget.cpp \
        src/BasicDec/ColorDec.c \
        src/Formatrans/Piclib.c \
        src/Formatrans/RGB2HSL.c \
        src/GUI/BasicGui.c \
        src/Hardbasic/arm_linux_hardpatch.c \
        src/IO/bmp.c \
        src/Mat/Mat.c \
        src/PicOr/GeoTrans.c \
        src/PicOr/MathOr.c \
        src/PicOr/PointOr.c \


INCLUDEPATH +=  \
              inc

HEADERS += \
    inc/widget.h \
    inc/arm_linux_hardpatch.h \
    inc/BasicGui.h \
    inc/bmp.h \
    inc/ColorDec.h \
    inc/cv.h \
    inc/font.h \
    inc/GeoTrans.h \
    inc/inffast.h \
    inc/inffixed.h \
    inc/inflate.h \
    inc/inftrees.h \
   inc/jconfig.h \
   inc/jerror.h \
   inc/jmorecfg.h \
   inc/jpeglib.h \
   inc/Mat.h \
   inc/MathOr.h \
   inc/Piclib.h \
   inc/png.h \
   inc/pngconf.h \
   inc/pngdebug.h \
   inc/pnginfo.h \
   inc/pnglibconf.h \
   inc/pngpriv.h \
   inc/pngstruct.h \
   inc/PointOr.h \
   inc/RGB2HSL.h \
   inc/trees.h \
   inc/turbojpeg.h \
   inc/widget.h \
    inc/zconf.h \
    inc/zlib.h \
    inc/zutil.h \
    inc/arm_linux_hardpatch.h \
    inc/BasicGui.h \
    inc/bmp.h \
    inc/ColorDec.h \
    inc/cv.h \
    inc/font.h \
    inc/GeoTrans.h \
    inc/inffast.h \
    inc/inffixed.h \
    inc/inflate.h \
    inc/inftrees.h \
    inc/jconfig.h \
    inc/jerror.h \
    inc/jmorecfg.h \
    inc/jpeglib.h \
    inc/Mat.h \
    inc/MathOr.h \
    inc/Piclib.h \
    inc/png.h \
    inc/pngconf.h \
    inc/pngdebug.h \
    inc/pnginfo.h \
    inc/pnglibconf.h \
    inc/pngpriv.h \
    inc/pngstruct.h \
    inc/PointOr.h \
    inc/RGB2HSL.h \
    inc/trees.h \
    inc/turbojpeg.h \
    inc/widget.h \
    inc/zconf.h \
    inc/zlib.h \
    inc/zutil.h

LIBS        +=F:\LITECV\LiteCV\lib\lib*

FORMS += \
        Qt/widget.ui
