#include "vector2d.hpp"
#include <math.h>

vector2d::vector2d ()
{
    this->x = 0, this->y = 0;
}

vector2d :: vector2d (double xN, double yN)
{
    this->x = xN, this->y = yN;
}

double vector2d::getX ()
{
    return this->x;
}
double vector2d::getY ()
{
    return this->y;
}

void vector2d::setX (double newX)
{
    this->x = newX;
}
void vector2d::setY (double newY)
{
    this->y = newY;
}

double vector2d::distance ()
{
    return std::sqrt ((this->x) * (this->x) + (this->y) * (this->y));
}
vector2d vector2d::operator +(vector2d other)
{
    vector2d tmp (this->x + other.getX (), this->y + other.getY ());
    return tmp;
}
vector2d vector2d::operator -(vector2d other)
{
    vector2d tmp (this->x - other.getX (), this->y - other.getY ());
    return tmp;
}
vector2d vector2d::operator *(double num)
{
    vector2d tmp (this->x * num, this->y * num);
    return tmp;
}
double vector2d::operator *(vector2d v)
{
    return x * v.getX() + y * v.getY();
}
double vector2d::operator %(vector2d v)
{
    return x * v.getY() - y * v.getX();
}
vector2d vector2d::operator /(double num)
{
    vector2d tmp (this->x / num, this->y / num);
    return tmp;
}

void vector2d::operator +=(vector2d other)
{
    *this = (*this + other);
}
void vector2d::operator -=(vector2d other)
{
     *this = (*this - other);
}
void vector2d::operator *=(double num)
{
    *this = (*this * num);
}
void vector2d::operator /=(double num)
{
    *this = (*this / num);
}

vector2d vector2d::direction ()
{
    return *this / this->distance ();
}
