#include <stdio.h>
#include "vector2d.hpp"
#include "body.hpp"
#include "universe.hpp"
vector2d constForce (body a, body b)
{
    double k = 0.1;
    vector2d aPos = a.getPosition();
    vector2d bPos = b.getPosition();
    return (aPos - bPos) * k;
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
    body b1(1), b2(2);
    b2.setPosition(vector2d(10,5));

    universe u;
    u.addBody(&b1);
    u.addBody(&b2);
    u.addForce(&gravitation);

    for(int i = 0; i < 1e2; i++)
    {
        u.print(EXPORT_UNIVERSE_PRINTING_MODE);
        u.update(1);
    }

    return 0;
}

