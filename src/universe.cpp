#include "universe.hpp"

#include <stdio.h>

void universe::addBody (const body& b)
{
    this->bodies.push_back (b);
}

void universe::removeBodyByIndex (int n)
{
    this->bodies.erase (this->bodies.begin () + n);
}

void universe::addForce (forceFunction f)
{
    this->forces.push_back (f);
}

void universe::update (double time)
{
    for (forceFunction f : forces) {
        for (int i = 0; i < bodies.size(); i++) {
            for (int j = 0; j < bodies.size(); j++) {
                if (i != j) {
                    bodies[i].applicateForce(bodies[j], f);
                }
            }
        }
    }
    for(body& a : this->bodies)
        a.move (time);
}

std::vector<body> universe::getBodies ()
{
    return this->bodies;
}

void universe::print (int mode)
{
    for(body& b : this->bodies)
    {
        vector2d pos = b.getPosition ();
        vector2d vel = b.getVelocity ();
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

void universe::move_all (vector2d offset)
{
    for (auto &b : bodies)
    {
        vector2d cur_pos = b.getPosition ();
        b.setPosition (cur_pos + offset);
    }
}
