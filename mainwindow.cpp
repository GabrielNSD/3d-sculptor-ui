#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogsave.h"
#include "sculptor.h"
#include "drawingscreen.h"
#include<cstdlib>
#include <QtDebug>
#include <QByteArray>

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

    connect(ui->actionPutVoxel,
            SIGNAL(triggered(bool)),
            ui->drawingArea,
            SLOT(putVoxelSelector()));

    connect(ui->actionCutVoxel,
            SIGNAL(triggered(bool)),
            ui->drawingArea,
            SLOT(cutVoxelSelector()));

    connect(ui->actionPutBox,
            SIGNAL(triggered(bool)),
            ui->drawingArea,
            SLOT(putBoxSelector()));

    connect(ui->actionCutBox,
            SIGNAL(triggered(bool)),
            ui->drawingArea,
            SLOT(cutBoxSelector()));

    connect(ui->actionPutSphere,
            SIGNAL(triggered(bool)),
            ui->drawingArea,
            SLOT(putSphereSelector()));

    connect(ui->actionCutSphere,
            SIGNAL(triggered(bool)),
            ui->drawingArea,
            SLOT(cutSphereSelector()));

    connect(ui->actionPutEllipsoid,
            SIGNAL(triggered(bool)),
            ui->drawingArea,
            SLOT(putEllipsoidSelector()));

    connect(ui->actionCutEllipsoid,
            SIGNAL(triggered(bool)),
            ui->drawingArea,
            SLOT(cutEllipsoidSelector()));

    connect(ui->horizontalSliderRadiusSphere,
            SIGNAL(valueChanged(int)),
            ui->drawingArea,
            SLOT(setSphereRadius(int)));

    //ellipsoid parameters
    connect(ui->horizontalSliderRadiusXElipsoid,
            SIGNAL(valueChanged(int)),
            ui->drawingArea,
            SLOT(setEllipsoidRx(int)));

    connect(ui->horizontalSliderRadiusYElipsoid,
            SIGNAL(valueChanged(int)),
            ui->drawingArea,
            SLOT(setEllipsoidRy(int)));

    connect(ui->horizontalSliderRadiusZElipsoid,
            SIGNAL(valueChanged(int)),
            ui->drawingArea,
            SLOT(setEllipsoidRz(int)));
    //xy plane depth
    connect(ui->horizontalSliderZ,
            SIGNAL(valueChanged(int)),
            ui->drawingArea,
            SLOT(setZ(int)));

    //box parameters
    connect(ui->horizontalSliderBoxX,
            SIGNAL(valueChanged(int)),
            ui->drawingArea,
            SLOT(setLengthX(int)));

    connect(ui->horizontalSliderBoxY,
            SIGNAL(valueChanged(int)),
            ui->drawingArea,
            SLOT(setLengthY(int)));

    connect(ui->horizontalSliderBoxZ,
            SIGNAL(valueChanged(int)),
            ui->drawingArea,
            SLOT(setLengthZ(int)));

//    connect(ui->pushButtonExit,
//            SIGNAL(clicked(bool)),
//            this,
//            SLOT(killAll()));

    connect(ui->actionOpenSaveDialog,
            SIGNAL(triggered()),
            this,
            SLOT(openDialogSave()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::killAll()
{
    exit(0);
}

void MainWindow::openDialogSave()
{

    if(d.exec() == QDialog::Accepted){
        if(d.grabText().isEmpty()) {
            return;
        } else{
        qDebug() << "ok" << d.grabText();
        QString teste;
        teste = d.grabText();
        QByteArray ba = teste.toLocal8Bit();
        char *c_str2 = ba.data();
        fileNameChar = c_str2;
        ui->drawingArea->saveFile(c_str2);
        }
    } else {
        qDebug() << "cancel" << d.grabText();
    }

}

void MainWindow::saveFile(char* filename)
{
    ui->drawingArea->saveFile(filename);
}

