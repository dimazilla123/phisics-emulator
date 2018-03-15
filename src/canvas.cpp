#include "canvas.hpp"

void Canvas::paintEvent (QPaintEvent *event)
{
}

Canvas::Canvas (QWidget *parent) : QWidget (parent)
{

}
Canvas::~Canvas ()
{
}

void Canvas::draw_points (std::vector<vector2d> *points)
{
    this->p = new QPolygon ();

    for (auto point : *points)
    {
        int x = point.getX (), y = point.getY ();
        *(this->p) << QPoint (x, y);
    }
    this->painter->drawPolyline (*(this->p));
    delete this->p;
}
