#include "body.hpp"

body::body (double m)
{
    this->forceSum = vector2d (0, 0);
    this->position = vector2d (0, 0);
    this->mass = m;
}

body::body(double m, std::vector<std::string> params)
{
    this->forceSum = vector2d ();
    this->velocity = vector2d ();
    this->mass = m;
    for(std::string name : params)
    {
        this->parameters.insert (std::pair<std::string,double> (name, 0));
    }
}

void body::setPosition (vector2d newPos)
{
    this->position = newPos;
}

vector2d body::getPosition () const
{
    return this->position;
}

void body::setVelocity (vector2d newVelocity)
{
    this->velocity = newVelocity;
}

vector2d body::getVelocity () const
{
    return this->velocity;
}

double body::getMass () const
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

void body::setParameter (std::string name, double value)
{
    this->parameters.insert (std::pair<std::string, double>(name, value));
}

double body::getParameter (std::string name) const
{
    return (this->parameters.find (name))->second;
}

void body::applicateForce (body &other, forceFunction f)
{
    fprintf(stderr, "force val: x = %f, y = %f\n", f(*this, other).getX(), f(*this, other).getY());
    this->forceSum += f(*this, other);
}
