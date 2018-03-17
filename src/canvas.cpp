#include "canvas.hpp"

void Canvas::paintEvent (QPaintEvent *event)
{
    QPainter paint (this);
    paint.setBrush(QBrush(Qt::blue, Qt::SolidPattern));
    paint.setPen (QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
    paint.drawPolyline (*(this->polygon));
}

Canvas::Canvas (QWidget *parent) : QWidget (parent)
{
    this->polygon = new QPolygon ();
}
Canvas::Canvas () : QWidget ()
{
    this->polygon = new QPolygon ();
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
    delete this->polygon;

    QVector<QPoint> figure;

    for (auto point : *points)
    {
        int x = point.getX (), y = point.getY ();
        figure.push_back (QPoint (x, y));
    }
    //figure.push_back (points->at(0));
    this->polygon = new QPolygon (figure);
    update ();
}
