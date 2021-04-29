#ifndef DRAWINGSCREEN_H
#define DRAWINGSCREEN_H

#include <QWidget>
#include <vector>
#include <string>
#include "sculptor.h"

using namespace std;

class DrawingScreen : public QWidget
{
    Q_OBJECT
private:
    int sizeX;
    int sizeY;
    int nrows;
    int ncols;
    int borderv;
    int borderh;

    float r,g,b,a=1;

    int drawingGeometry; // 0/1= put/cut Voxel, 2/3 = put/cut box, 4/5 = put/cut sphere, 6/7 = Ellipsoid
    bool pressed;

    Sculptor *m;

    vector <vector <Voxel>> v;
public:
    explicit DrawingScreen(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);

    void mousePressEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void loadMatrix(vector <vector<Voxel>> m);

    void drawGeometry(int _drawingGeometry, int posX, int posY);

 public slots:
    void setSize(int newSize);
    void setRed(int _r);
    void setGreen(int _g);
    void setBlue(int _b);

    void putVoxelSelector();
    void cutVoxelSelector();
    void putBoxSelector();
    void cutBoxSelector();
    void putSphereSelector();
    void cutSphereSelector();
    void putEllipsoidSelector();
    void cutEllipsoidSelector();

signals:
    void changedX(int);
    void changedY(int);
    void updatePos(int,int);


};

#endif // DRAWINGSCREEN_H
