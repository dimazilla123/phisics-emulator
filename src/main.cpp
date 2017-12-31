#include <stdio.h>
#include "vector2d.hpp"
#include "body.hpp"

int main()
{
    body b(10);
    b.setPosition(vector2d(0, 0));
    b.setVelocity(vector2d(10,5));
    printf("%lf %lf\n", b.getPosition().getX(), b.getPosition().getY());
    b.move(0.5);
    printf("%lf %lf\n", b.getPosition().getX(), b.getPosition().getY());

    return 0;
}

