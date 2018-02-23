#include <stdio.h>
#include <stdlib.h>
#include "vector2d.hpp"
#include "body.hpp"
#include "universe.hpp"
#include "interface.hpp"

using namespace sf;

vector2d constForce (body a, body b)
{
    double k = 20;
    vector2d aPos = a.getPosition ();
    vector2d bPos = b.getPosition ();
    return (bPos - aPos).direction () * k;
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

    body b1 (1), b2 (1);

    b1.setPosition (vector2d (wight / 2 + 10, hight / 2));
    b2.setPosition (vector2d (wight / 2 - 10, hight / 2));

    b1.setVelocity (vector2d (0, 30));
    b2.setVelocity (vector2d (0, -10));

    universe u;
    u.addBody (&b1);
    u.addBody (&b2);
    u.addForce (&constForce);

    interface interf (u, wight, hight, speed);
    interf.run (time);

    return 0;
}

