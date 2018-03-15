#include "canvas.hpp"

void Canvas::paintEvent (QPaintEvent *event)
{
    this->painter->drawPolyline (*(this->p));
}

Canvas::Canvas (QWidget *parent) : QWidget (parent)
{
    this->painter = new QPainter (this);
    this->painter->setBrush(QBrush(Qt::black, Qt::SolidPattern));
}
Canvas::~Canvas ()
{
}

void Canvas::draw_points (std::vector<vector2d> *points)
{
    delete this->p;
    this->p = new QPolygon ();

    for (auto point : *points)
    {
        int x = point.getX (), y = point.getY ();
        *(this->p) << QPoint (x, y);
    }
    repaint ();
}
