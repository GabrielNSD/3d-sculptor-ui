#include "dialogsave.h"
#include "ui_dialogsave.h"
#include "sculptor.h"

DialogSave::DialogSave(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSave)
{
    ui->setupUi(this);
}

DialogSave::~DialogSave()
{
    delete ui;
}

QString DialogSave::grabText()
{
    return  ui->lineEditSaveName->text();
}
