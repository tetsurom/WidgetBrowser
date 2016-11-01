
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WidgetBrowser
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    wb/dialog.cpp \
    wb/treeitem.cpp \
    wb/widgettreemodel.cpp \
    wb/widgettree.cpp \
    wb/capturelabel.cpp \
    wb/listener.cpp \

HEADERS += \
    wb/dialog.h \
    wb/treeitem.h \
    wb/widgettreemodel.h \
    wb/widgettree.h \
    wb/capturelabel.h \
    wb/listener.h \
