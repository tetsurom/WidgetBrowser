#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../src/wb/dialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_2, &QPushButton::clicked, [](){
        wb::WbDialog dialog;
        dialog.exec();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
