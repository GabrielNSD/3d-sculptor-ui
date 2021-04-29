#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<cstdlib>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->horizontalSliderDimension,
            SIGNAL(valueChanged(int)),
            ui->drawingArea,
            SLOT(setSize(int)));

    connect(ui->horizontalSliderRed,
            SIGNAL(valueChanged(int)),
            ui->drawingArea,
            SLOT(setRed(int)));

    connect(ui->horizontalSliderGreen,
            SIGNAL(valueChanged(int)),
            ui->drawingArea,
            SLOT(setGreen(int)));

    connect(ui->horizontalSliderBlue,
            SIGNAL(valueChanged(int)),
            ui->drawingArea,
            SLOT(setBlue(int)));


//    connect(ui->pushButtonExit,
//            SIGNAL(clicked(bool)),
//            this,
//            SLOT(killAll()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::killAll()
{
    exit(0);
}

