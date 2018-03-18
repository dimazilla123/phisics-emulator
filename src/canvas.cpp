#include "canvas.hpp"

void Canvas::paintEvent (QPaintEvent *event)
{
    QPainter paint (this);
    paint.setBrush(QBrush(Qt::blue, Qt::SolidPattern));
    paint.setPen (QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
    for (auto point : body_positions)
    {
        paint.drawEllipse (point, 10, 10);
    }
}

Canvas::Canvas (QWidget *parent) : QWidget (parent)
{
    this->setStyleSheet ("background-color:white;");
}
Canvas::Canvas () : QWidget ()
{
    this->setStyleSheet ("background-color:white;");
}
Canvas::~Canvas ()
{
}

void Canvas::redraw ()
{
    update ();
}

void Canvas::draw_points (std::vector<vector2d> *points)
{
    this->body_positions.clear ();

    for (auto point : *points)
    {
        double x = point.getX (), y = point.getY ();
        this->body_positions.push_back (QPointF (x, y));
    }
    update ();
}
