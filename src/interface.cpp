#include "interface.hpp"
#include <vector>

interface::interface (universe vers, int w, int h, double s)
{
    this->u = vers;
    this->speed = s;
    this->canvas = new Canvas(this);
}

interface::~interface ()
{
}

void interface::move (double x, double y)
{
}

void interface::run (double time)
{
    this->show ();
    std::vector<vector2d> positions;
    for (auto body_ptr : this->u.getBodies ())
    {
        positions.push_back (body_ptr->getPosition ());
    }
    this->canvas->draw_points (&positions);
    positions.erase (positions.begin (), positions.end ());
}
