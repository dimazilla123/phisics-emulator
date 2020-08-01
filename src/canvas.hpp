#include <QWidget>
#include <QPainter>
#include <QPolygon>
#include "vector2d.hpp"
#include <vector>
#include <QVector>
#include <QResizeEvent>
#include <QWheelEvent>
#include <iostream>

/*
 * Custom widget for drawing
 */

class Canvas : public QWidget
{
    Q_OBJECT
public:
    QPainter* painter;
    void drawPoints(const std::vector<vector2d> &points);
    Canvas(QWidget *parent);
    Canvas();
    ~Canvas();
public slots:
    void redraw();
private:
    QVector<QPointF> body_positions;
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

    int w, h;
    double x1, y1, x2, y2;
    bool first_resize = true;

    // for scrolling
    bool ispanning = false;
    int anc_x, anc_y;
    double zoom = 1;
};
