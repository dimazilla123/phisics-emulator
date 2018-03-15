#ifndef INTERFACE_H
#define INTERFACE_H

#include <QApplication>
#include <QWidget>
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
    public:
        interface (universe vers, int w, int h, double speed);
        ~interface ();
        //void setSize(int x, int y);
        void move (double x, double y);
        void run (double time);
};

#endif
