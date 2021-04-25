#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<cstdlib>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    connect(ui->pushButtonExit,
            SIGNAL(clicked(bool)),
            this,
            SLOT(killAll()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::killAll()
{
    exit(0);
}

