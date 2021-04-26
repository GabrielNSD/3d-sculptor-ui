#include "drawingscreen.h"
#include <QPainter>
#include <QBrush>
#include <QPen>

DrawingScreen::DrawingScreen(QWidget *parent) : QWidget(parent)
{

}

void DrawingScreen::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QBrush brush;
    QPen pen;

    brush.setColor(QColor(192,192,192));
    brush.setStyle(Qt::SolidPattern);

    pen.setColor(QColor(96,96,96));
    pen.setWidth(2);

    painter.setBrush(brush);
    painter.setPen(pen);
    painter.drawRect(0,0, width(),height());
}

void DrawingScreen::loadMatrix(vector<vector<Voxel> > m)
{
    nrows = m.size();
    ncols = m[0].size();
    v = m;
    repaint();
}
