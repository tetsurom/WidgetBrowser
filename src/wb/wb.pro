
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WidgetBrowser
TEMPLATE = lib

SOURCES += \
    dialog.cpp \
    treeitem.cpp \
    widgettreemodel.cpp \
    widgettree.cpp \
    capturelabel.cpp \
    listener.cpp \

HEADERS += \
    dialog.h \
    treeitem.h \
    widgettreemodel.h \
    widgettree.h \
    capturelabel.h \
    listener.h \
