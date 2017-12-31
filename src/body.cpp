#include "body.hpp"

body :: body(double m)
{
    this->mass = m;
}

void body :: setPosition(vector2d newPos)
{
    this->position = newPos;
}

vector2d body :: getPosition()
{
    return this->position;
}

void body :: setVelocity(vector2d newVelocity)
{
    this->velocity = newVelocity;
}

vector2d body :: getVelocity()
{
    return this->velocity;
}

void body :: move(double dt)
{
    this->position += this->velocity * dt;
}
