#include "canvas.hpp"
#include <cmath>

void Canvas::paintEvent(QPaintEvent *event)
{
    QPainter paint(this);
    paint.setBrush(QBrush(Qt::blue, Qt::SolidPattern));
    paint.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
    for (auto point : body_positions)
    {
        double x = point.x();
        double y = point.y();
        x -= x1;
        y -= y1;
        x = w * x / (x2 - x1);
        y = h * y / (y2 - y1);
        paint.drawEllipse({x, y}, 10, 10);
    }
}

void Canvas::resizeEvent(QResizeEvent *event)
{
    w = event->size().width();
    h = event->size().height();
    if (first_resize) {
        x2 = w;
        y2 = h;
        first_resize = false;
    }
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        ispanning = true;
        anc_x = event->x();
        anc_y = event->y();
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        ispanning = false;
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    if (ispanning) {
        int x = event->x();
        int y = event->y();
        x1 -= (x - anc_x) * (x2 - x1) / w;
        x2 -= (x - anc_x) * (x2 - x1) / w;
        y1 -= (y - anc_y) * (y2 - y1) / h;
        y2 -= (y - anc_y) * (y2 - y1) / h;
        anc_x = x;
        anc_y = y;
    }
}

void Canvas::wheelEvent(QWheelEvent *event)
{
    double cx = (x1 + x2) / 2;
    double cy = (y1 + y2) / 2;
    double dx = x2 - cx;
    double dy = y2 - cy;
    double mul = std::pow(0.5, event->delta() / 120);
    dx *= mul;
    dy *= mul;
    /*
    if (event->delta() < 0) {
        dx *= 2;
        dy *= 2;
    } else {
        dx *= 0.5;
        dy *= 0.5;
    }
    */
    x1 = cx - dx;
    x2 = cx + dx;
    y1 = cy - dy;
    y2 = cy + dy;
}

Canvas::Canvas(QWidget *parent) : QWidget(parent)
{
    this->setStyleSheet("background-color:white;");
    x1 = y1 = 0;
    x2 = this->frameSize().width();
    y2 = this->frameSize().height();
}
Canvas::Canvas() : QWidget()
{
    this->setStyleSheet("background-color:white;");
}

Canvas::~Canvas()
{

}

void Canvas::redraw()
{
    update();
}

void Canvas::drawPoints(const std::vector<vector2d> &points)
{
    this->body_positions.clear();

    for (auto point : points)
    {
        double x = point.getX(), y = point.getY();
        this->body_positions.push_back(QPointF(x, y));
    }
    update();
}
