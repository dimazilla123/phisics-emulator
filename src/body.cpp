#include "body.hpp"

Body::Body (double m)
{
    this->forceSum = vector2d (0, 0);
    this->position = vector2d (0, 0);
    this->mass = m;
}

Body::Body(double m, std::vector<std::string> params)
{
    this->forceSum = vector2d ();
    this->velocity = vector2d ();
    this->mass = m;
    for(std::string name : params)
    {
        this->parameters.insert (std::pair<std::string,double> (name, 0));
    }
}

void Body::setPosition (vector2d newPos)
{
    this->position = newPos;
}

vector2d Body::getPosition () const
{
    return this->position;
}

void Body::setVelocity (vector2d newVelocity)
{
    this->velocity = newVelocity;
}

vector2d Body::getVelocity () const
{
    return this->velocity;
}

double Body::getMass () const
{
    return this->mass;
}

void Body::setMass (double m)
{
    this->mass = m;
}

void Body::move (double dt)
{
    velocity += this->forceSum * dt / this->mass;
    this->forceSum = vector2d ();
    this->position += this->velocity * dt;
}

void Body::setParameter (std::string name, double value)
{
    this->parameters.insert (std::pair<std::string, double>(name, value));
}

double Body::getParameter (std::string name) const
{
    return (this->parameters.find (name))->second;
}

void Body::applicateForce (Body &other, forceFunction f)
{
    fprintf(stderr, "force val: x = %f, y = %f\n", f(*this, other).getX(), f(*this, other).getY());
    this->forceSum += f(*this, other);
}
