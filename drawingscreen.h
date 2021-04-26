#ifndef DRAWINGSCREEN_H
#define DRAWINGSCREEN_H

#include <QWidget>
#include <vector>
#include "sculptor.h"

using namespace std;

class DrawingScreen : public QWidget
{
    Q_OBJECT
private:
    int nrows;
    int ncols;

    vector <vector <Voxel>> v;
public:
    explicit DrawingScreen(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);

    void mousePressEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    void loadMatrix(vector <vector<Voxel>> m);

signals:

};

#endif // DRAWINGSCREEN_H
