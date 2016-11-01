
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WidgetBrowserExample
TEMPLATE = app

SOURCES += main.cpp \
        mainwindow.cpp

HEADERS += mainwindow.h

FORMS   += mainwindow.ui

INCLUDEPATH  += ../src
debug {
    LIBS += -L../src/debug -lWidgetBrowser
} else {
    LIBS += -L../src/release -lWidgetBrowser
}
