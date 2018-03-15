#include "body.hpp"

body::body (double m)
{
    this->forceSum = vector2d (0, 0);
    this->position = vector2d (0, 0);
    this->mass = m;
}

body::body(double m, vector<string> params)
{
    this->forceSum = vector2d ();
    this->velocity = vector2d ();
    this->mass = m;
    for(string name : params)
    {
        this->parameters.insert (pair<string,double> (name, 0));
    }
}

void body::setPosition (vector2d newPos)
{
    this->position = newPos;
}

vector2d body::getPosition ()
{
    return this->position;
}

void body::setVelocity (vector2d newVelocity)
{
    this->velocity = newVelocity;
}

vector2d body::getVelocity ()
{
    return this->velocity;
}

double body::getMass ()
{
    return this->mass;
}

void body::setMass (double m)
{
    this->mass = m;
}

void body::move (double dt)
{
    velocity += this->forceSum * dt / this->mass;
    this->forceSum = vector2d ();
    this->position += this->velocity * dt;
}

void body::setParameter (string name, double value)
{
    this->parameters.insert (pair<string, double>(name, value));
}

double body::getParameter (string name)
{
    return (this->parameters.find (name))->second;
}

void body::applicateForce (body other, vector2d (*force)(body, body))
{
    this->forceSum += (*force)(*this, other);
}
