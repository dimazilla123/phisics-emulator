#include <QWidget>
#include <QPainter>
#include <QPolygon>
#include "vector2d.hpp"
#include <vector>
#include <QVector>
#include <iostream>

/*
 * Custom widget for drawing
 */

class Canvas : public QWidget
{
    Q_OBJECT
private:
    QVector<QPointF> body_positions;
protected:
    void paintEvent (QPaintEvent *event);
public:
    QPainter* painter;
    void draw_points (std::vector<vector2d> *points);
    Canvas (QWidget *parent);
    Canvas ();
    ~Canvas();
public slots:
    void redraw ();
};
