#ifndef DIALOGSAVE_H
#define DIALOGSAVE_H

#include <QDialog>
#include <QString>

namespace Ui {
class DialogSave;
}

class DialogSave : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSave(QWidget *parent = nullptr);
    ~DialogSave();
    QString grabText();


private:
    Ui::DialogSave *ui;
};

#endif // DIALOGSAVE_H
