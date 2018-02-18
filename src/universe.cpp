#include "universe.hpp"

#include <stdio.h>

void universe::addBody (body *b)
{
    this->bodies.push_back (b);
}

void universe::addForce (forceFunction f)
{
    this->forces.push_back (f);
}

void universe::update (double time)
{
    for(forceFunction f : this->forces)
    for(body* a : this->bodies)
    {
        for(body* b : this->bodies)
        {
            if(a != b)
            {
                a->applicateForce (*b, f);
                b->applicateForce (*a, f);
            }
        }
    }

    for(body* a : this->bodies)
        a->move (time);
}

vector<body*> universe::getBodies ()
{
    return this->bodies;
}

void universe::print (int mode)
{
    for(body* b : this->bodies)
    {
        vector2d pos = b->getPosition ();
        vector2d vel = b->getVelocity ();
        if(mode == READABLE_UNIVERSE_PRINTING_MODE)
        {
            printf ("position %lf %lf\n", pos.getX (), pos.getY ());
            printf ("velocity %lf %lf\n", vel.getX (), vel.getY ());
            getchar ();
        }
        if(mode == EXPORT_UNIVERSE_PRINTING_MODE)
        {
            printf("%lf %lf ", pos.getX (), pos.getY ());
            printf("%lf %lf ", vel.getX (), vel.getY ());
        }
    }
    putchar('\n');
}
