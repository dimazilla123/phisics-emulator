#include <QWidget>
#include <QPainter>
#include <QPolygon>
#include "vector2d.hpp"
#include <vector>

class Canvas : public QWidget
{
    Q_OBJECT
private:
    QPolygon *p;
protected:
    void paintEvent (QPaintEvent *event);
public:
    QPainter* painter;
    void draw_points (std::vector<vector2d> *points);
    Canvas(QWidget *parent);
    ~Canvas();
};
