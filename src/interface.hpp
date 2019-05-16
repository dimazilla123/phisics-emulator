#ifndef INTERFACE_H
#define INTERFACE_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QCheckBox>
#include <QTimer>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QShortcut>
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
        QGroupBox* body_add_widget;
        QLineEdit* mass_input;
        QLineEdit* pos_x_input;
        QLineEdit* pos_y_input;
        QLineEdit* vel_x_input;
        QLineEdit* vel_y_input;
    public:
        interface (universe vers, int w, int h, double speed);
        ~interface ();
        void move (double x, double y);
        void run (double time);
    public slots:
        void move_up();
        void move_down();
        void move_left();
        void move_right();
        void update_universe();
        void update_canvas();
        void addBody();
};

#endif
