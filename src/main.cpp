#include <stdio.h>
#include "vector2d.hpp"
#include "body.hpp"
#include "universe.hpp"
#include "interface.hpp"

using namespace sf;

vector2d constForce (body a, body b)
{
    double k = 2;
    vector2d aPos = a.getPosition();
    vector2d bPos = b.getPosition();
    return (bPos - aPos) / (aPos - bPos).distance() * k;
}

vector2d gravitation (body a, body b)
{
    double G = 6.7;
    vector2d aPos = a.getPosition();
    vector2d bPos = b.getPosition();
    double m1 = a.getMass(), m2 = b.getMass();
    double r = (aPos - bPos).distance();
    return (bPos - aPos).direction() * G * m1 * m2 / (r * r);
}

int main()
{
    const int wight = 900, hight = 600;
    body b1(1), b2(1), b3(1);
    b1.setPosition(vector2d(wight / 2, hight / 2));
    b1.setVelocity(vector2d(0,-10));
    b2.setPosition(vector2d(wight / 2 + 100, hight / 2));
    b3.setPosition(vector2d(wight / 2 + 200, hight / 2 + 50));
    //b2.setVelocity(vector2d(0,-1));

    universe u;
    u.addBody(&b1);
    u.addBody(&b2);
    u.addBody(&b3);
    u.addForce(&constForce);

    interface interf(u, wight, hight, 10);
    interf.run(0.001);

    return 0;
}

