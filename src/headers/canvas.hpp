#include <QWidget>
#include <QPainter>
#include <QPolygon>
#include "vector2d.hpp"
#include <vector>
#include <QVector>
#include <iostream>

class Canvas : public QWidget
{
    Q_OBJECT
private:
    QPolygon *polygon;
private slots:
    void redraw ();
protected:
    void paintEvent (QPaintEvent *event);
public:
    QPainter* painter;
    void draw_points (std::vector<vector2d> *points);
    Canvas (QWidget *parent);
    Canvas ();
    ~Canvas();

};
