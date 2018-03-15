#include <stdio.h>
#include <stdlib.h>
#include <QApplication>
#include "vector2d.hpp"
#include "body.hpp"
#include "universe.hpp"
#include "interface.hpp"

vector2d constForce (body a, body b)
{
    double k = 20;
    vector2d aPos = a.getPosition ();
    vector2d bPos = b.getPosition ();
    return (bPos - aPos).direction () * k;
}

vector2d goock_force (body a, body b)
{
    double k = 20;
    vector2d aPos = a.getPosition ();
    vector2d bPos = b.getPosition ();
    return (bPos - aPos) * k;
}

vector2d gravitation (body a, body b)
{
    double G = 1;
    vector2d aPos = a.getPosition ();
    vector2d bPos = b.getPosition ();
    double m1 = a.getMass (), m2 = b.getMass ();
    double r = (aPos - bPos).distance ();
    return (bPos - aPos).direction () * G * m1 * m2 / (r * r);
}

int main(int argc, char** argv)
{
    int wight = 900, hight = 600;
    double time = 0.001, speed = 1;
    if(argc > 1) time = atof (argv[1]);
    if(argc > 2) wight == atoi (argv[2]);
    if(argc > 3) hight = atoi (argv[3]);
    if(argc > 4) speed = atof (argv[4]);

    universe u;
    u.addForce (&goock_force);

    body b1 (1), b2(2);
    b1.setPosition (vector2d (200, 200));
    b2.setPosition (vector2d (300, 200));

    QApplication app (argc, argv);

    interface interf (u, wight, hight, speed);
    interf.show ();
    interf.run (time);

    app.exec ();

    return 0;
}

