#include "drawingscreen.h"
#include "sculptor.h"
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QMouseEvent>
#include <QRect>

DrawingScreen::DrawingScreen(QWidget *parent) : QWidget(parent)
{
        sizeX =sizeY=sizeZ=199;

        m = new Sculptor(sizeX, sizeY, sizeZ);
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

    for(float i=(height()/sizeY)+borderv;i<=height(); i=i+(height()/sizeY)){
        painter.drawLine(0,i,width(),i);
    }

    for(int i=0; i<sizeX; i++){
           for(int j=0; j<sizeY; j++){
               for(int k=0; k<sizeZ; k++){
                   if(m->isOn(i, j, k) == 1 && posZ == k){
                       brush.setColor(QColor(m->getRed(i,j,k),m->getGreen(i,j,k),m->getBlue(i,j,k)));
                       brush.setStyle(Qt::SolidPattern);
                       painter.setBrush(brush);
                       painter.drawEllipse(i*(width()/sizeX), j*(height()/sizeY), width()/sizeX, height()/sizeY);
                   }
               }
           }
       }
}

void DrawingScreen::mousePressEvent(QMouseEvent *event)
{
    int posX, posY;
//    QRect ret;
//    ret = rect();
//    pressed = true;
//    ret.adjust(borderh,borderv,-borderh,-borderv);
//    if(ret.contains(event->pos())){
//        posX = (event->pos().x()-borderh)*ncols/ret.width();
//        posY = (event->pos().y()-borderv)*nrows/ret.height();
//        emit updatePos(posX,posY);
//    }
//    emit changedX(event->x());
//    emit changedY(event->y());

    emit changedX(event->x());
    emit changedY(event->y());
    posX = event->x()/(width()/sizeX);
    posY = event->y()/(height()/sizeY);
    pressed = true;

    drawGeometry(drawingGeometry, posX, posY, posZ);

}

void DrawingScreen::mouseMoveEvent(QMouseEvent *event)
{
    int posX, posY;
    emit changedX(event->x());
    emit changedY(event->y());

    posX = event->x()/(width()/sizeX);
    posY = event->y()/(height()/sizeY);

    if(pressed){
        drawGeometry(drawingGeometry, posX, posY, posZ);
    }
}

void DrawingScreen::mouseReleaseEvent(QMouseEvent *event)
{
    pressed = false;
    repaint();
}

void DrawingScreen::loadMatrix(vector<vector<Voxel> > m)
{
    nrows = m.size();
    ncols = m[0].size();
    //v = m;
    repaint();
}

void DrawingScreen::drawGeometry(int _drawingGeometry, int _posX, int _posY, int _posZ)
{
    switch (_drawingGeometry) {
    case 0:
        m->setColor(r/255,g/255,b/255,a);
        m->putVoxel(_posX, _posY, _posZ);
        break;

    case 1:
        m->cutVoxel(_posX, _posY, _posZ);
        break;

    case 2:
        m->setColor(r/255,g/255,b/255,a);
        m->putBox(_posX-(lenghtX/2), _posX+(lenghtX/2), _posY-(lenghtY/2), _posY+(lenghtY/2), _posZ-(lenghtZ/2), _posZ+(lenghtZ/2));
        break;

    case 3:
        m->cutBox(_posX-(lenghtX/2), _posX+(lenghtX/2), _posY-(lenghtY/2), _posY+(lenghtY/2), _posZ-(lenghtZ/2), _posZ+(lenghtZ/2));
        break;

    case 4:
        m->setColor(r/255,g/255,b/255,a);
        m->putSphere(_posX,_posY,_posZ, radius);
        break;

    case 5:
        m->cutSphere(_posX,_posY,_posZ, radius);
        break;

    case 6:
        m->setColor(r/255,g/255,b/255,a);
        m->putEllipsoid(_posX, _posY, _posZ, radiusX, radiusY, radiusZ);
        break;

    case 7:
        m->cutEllipsoid(_posX, _posY, _posZ, radiusX, radiusY, radiusZ);
        break;

    }
}

void DrawingScreen::saveFile(char *filename)
{
    m->writeOFF(filename);
}

void DrawingScreen::setSize(int newSize)
{
    sizeX = sizeY = newSize;
    repaint();
}

void DrawingScreen::setRed(int _r)
{
    r = _r;
    repaint();
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
    repaint();
}

void DrawingScreen::setLengthX(int _lengthX)
{
    lenghtX = _lengthX;
    repaint();
}

void DrawingScreen::setLengthY(int _lengthY)
{
    lenghtY = _lengthY;
    repaint();
}

void DrawingScreen::setLengthZ(int _lengthZ)
{
    lenghtZ = _lengthZ;
    repaint();
}

void DrawingScreen::setSphereRadius(int _radius)
{
    radius = _radius;
}

void DrawingScreen::setEllipsoidRx(int _radiusX)
{
    radiusX = _radiusX;
}


void DrawingScreen::setEllipsoidRy(int _radiusY)
{
    radiusY = _radiusY;
}

void DrawingScreen::setEllipsoidRz(int _radiusZ)
{
    radiusZ = _radiusZ;
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
