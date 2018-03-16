#include "interface.hpp"
#include <vector>

interface::interface (universe vers, int w, int h, double s)
{
    this->u = vers;
    this->speed = s;
    this->canvas = new Canvas(this);
    this->canvas->resize (300, 300);
    QPushButton *but = new QPushButton ("Update", this);
    connect (but, SIGNAL(clicked ()), this, SLOT(update_universe ()));
    connect (but, SIGNAL(clicked ()), this->canvas, SLOT(redraw ()));
}

interface::~interface ()
{
}

void interface::move (double x, double y)
{
}

void interface::update_universe ()
{
    this->u.update (this->time);
    std::vector<vector2d> positions;
    for (auto body_ptr : this->u.getBodies ())
    {
        positions.push_back (body_ptr->getPosition ());
    }
    this->canvas->draw_points (&positions);
    positions.erase (positions.begin (), positions.end ());
}

void interface::run (double time)
{
    this->show ();
    this->time = time;
}
