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
#include <QMenuBar>
#include <QMenu>
#include <QShortcut>
#include "universe.hpp"
#include "canvas.hpp"
#include "formula_table.hpp"

class Interface : public QWidget
{
    Q_OBJECT
    private:
        Canvas *canvas;
        int h, w;
        Universe u;
        double speed;
        double time;
        QMenuBar* bar;
        QCheckBox* update_initor;
        QGroupBox* body_add_widget;
        QLineEdit* mass_input;
        QLineEdit* pos_x_input;
        QLineEdit* pos_y_input;
        QLineEdit* vel_x_input;
        QLineEdit* vel_y_input;
    public:
        Interface(Universe vers, int w, int h, double speed);
        ~Interface();
        void move(double x, double y);
        void run(double time);
    public slots:
        void save();
        void load();
        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();
        void updateUniverse();
        void updateCanvas();
        void addBody();
};

#endif
