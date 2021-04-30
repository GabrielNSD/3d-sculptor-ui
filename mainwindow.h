#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "dialogsave.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    DialogSave d;
    char* fileNameChar;

public slots:
    void killAll();
    void openDialogSave(void);
    void saveFile(char* filename);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
