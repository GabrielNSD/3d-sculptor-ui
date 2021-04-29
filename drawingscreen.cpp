#include "drawingscreen.h"
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QMouseEvent>
#include <QRect>

DrawingScreen::DrawingScreen(QWidget *parent) : QWidget(parent)
{
        sizeX =sizeY=10;
}

void DrawingScreen::mouseMoveEvent(QMouseEvent *event)
{
    emit changedX(event->x());
    emit changedY(event->y());
}

void DrawingScreen::mouseReleaseEvent(QMouseEvent *event)
{
    pressed = false;
}


void DrawingScreen::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QBrush brush;
    QPen pen;

    //grey brush
    brush.setColor(QColor(192,192,192));
    brush.setStyle(Qt::SolidPattern);

    //dark grey brush
    pen.setColor(QColor(96,96,96));
    pen.setWidth(2);
    borderh = borderv = 2;

    painter.setBrush(brush);
    painter.setPen(pen);
    painter.drawRect(0,0, width(),height());

    for(float i=(width()/sizeX)+borderh; i<=width(); i=i+(width()/sizeX)){
        painter.drawLine(i, 0, i, height());
     }

    for(float i=(height()/sizeY)+borderv;i<=height(); i=i+(width()/sizeY)){
        painter.drawLine(0,i,width(),i);
    }
}

void DrawingScreen::mousePressEvent(QMouseEvent *event)
{
    int posh, posv;
    QRect ret;
    ret = rect();
    pressed = true;
    ret.adjust(borderh,borderv,-borderh,-borderv);
    if(ret.contains(event->pos())){
        posh = (event->pos().x()-borderh)*ncols/ret.width();
        posv = (event->pos().y()-borderv)*nrows/ret.height();
        emit updatePos(posh,posv);
    }
    emit changedX(event->x());
    emit changedY(event->y());

}


void DrawingScreen::loadMatrix(vector<vector<Voxel> > m)
{
    nrows = m.size();
    ncols = m[0].size();
    v = m;
    repaint();
}

void DrawingScreen::drawGeometry(int _drawingGeometry, int _posX, int _posY, int _posZ)
{
    switch (_drawingGeometry) {
    case 0:
        m->setColor(r,g,b,a);
        m->putVoxel(_posX, _posY, _posZ);
        break;

    case 1:
        m->cutVoxel(_posX, _posY, _posZ);
        break;

    case 2:
        m->setColor(r,g,b,a);
        m->putBox(_posX-(lenghtX/2), _posX+(lenghtX/2), posY-(lenghtY/2), posY+(lenghtY/2), posZ-(lenghtZ/2), posZ+(lenghtZ/2));
        break;

    case 3:
        m->cutBox(_posX-(lenghtX/2), _posX+(lenghtX/2), posY-(lenghtY/2), posY+(lenghtY/2), posZ-(lenghtZ/2), posZ+(lenghtZ/2));
        break;

    case 4:
        m->setColor(r,g,b,a);
        m->putSphere(_posX,_posY,_posZ, radius);
        break;

    case 5:
        m->cutSphere(_posX,_posY,_posZ, radius);
        break;

    case 6:
        m->setColor(r,g,b,a);
        m->putEllipsoid(_posX, _posY, _posZ, radiusX, radiusY, radiusZ);
        break;

    case 7:
        m->cutEllipsoid(_posX, _posY, _posZ, radiusX, radiusY, radiusZ);
        break;

    }
}

void DrawingScreen::setSize(int newSize)
{
    sizeX = sizeY = newSize;
    repaint();
}

void DrawingScreen::setRed(int _r)
{
    r = _r;
}

void DrawingScreen::setGreen(int _g)
{
    g = _g;
}

void DrawingScreen::setBlue(int _b)
{
    b = _b;
}

void DrawingScreen::setZ(int _posZ)
{
    posZ = _posZ;
}

void DrawingScreen::putVoxelSelector(){
    drawingGeometry = 0;
}

void DrawingScreen::cutVoxelSelector(){
    drawingGeometry =1;
}

void DrawingScreen::putBoxSelector()
{
    drawingGeometry = 2;
}

void DrawingScreen::cutBoxSelector()
{
    drawingGeometry = 3;
}

void DrawingScreen::putSphereSelector()
{
    drawingGeometry = 4;
}

void DrawingScreen::cutSphereSelector()
{
    drawingGeometry = 5;
}

void DrawingScreen::putEllipsoidSelector()
{
    drawingGeometry = 6;
}

void DrawingScreen::cutEllipsoidSelector()
{
    drawingGeometry = 7;
}
