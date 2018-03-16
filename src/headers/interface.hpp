#ifndef INTERFACE_H
#define INTERFACE_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QCheckBox>
#include <QTimer>
#include <QGridLayout>
#include "universe.hpp"
#include "canvas.hpp"

class interface : public QWidget
{
    Q_OBJECT
    private:
        Canvas *canvas;
        int h, w;
        universe u;
        double speed;
        double time;
        QCheckBox* update_initor;
    public:
        interface (universe vers, int w, int h, double speed);
        ~interface ();
        void move (double x, double y);
        void run (double time);
    public slots:
        void update_universe ();
};

#endif
