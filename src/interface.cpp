#include "interface.hpp"

using namespace sf;

interface::interface (universe vers, int w, int h, double s)
{
    this->u = vers;
    this->speed = s;
    this->window = new RenderWindow (VideoMode (w,h), "interface");
    this->view = this->window->getDefaultView ();
    this->window->setFramerateLimit (220);
}

void interface::move (int x, int y)
{
    this->view.move(x,y);
}

void interface::run (double time)
{
    while(this->window->isOpen ())
    {
        Event event;
        vector<Vertex> figure;
        while(this->window->pollEvent (event))
        {
            while(Keyboard::isKeyPressed (Keyboard::Space))
            {
                figure.clear ();
                vector<body*> bodies = this->u.getBodies ();
                for(body *b : bodies)
                {
                    vector2d posBody = b->getPosition ();
                    Vector2f position (posBody.getX (), posBody.getY ());
                    Vertex vert (position, Color :: Black);
                    figure.push_back (vert);
                }
                figure.push_back (figure[0]);
                //u.print(EXPORT_UNIVERSE_PRINTING_MODE);
                u.update (time);
                this->window->setView (this->window->getDefaultView ());
                this->window->clear (Color :: White);
                this->window->draw (&figure[0], figure.size (), LineStrip);
                this->window->setView (this->view);
                this->window->display ();
            }
            while(Keyboard::isKeyPressed (Keyboard::T))
            {
                printf ("Body's mass: ");
                double m;
                scanf ("%lf", &m);
                printf ("Body's speed: ");
                double x_vel, y_vel;
                scanf("%lf %lf", &x_vel, &y_vel);
                printf ("Body's position: ");
                double x, y;
                scanf("%lf %lf", &x, &y);
                vector2d pos = vector2d (x, y), vel = vector2d (x_vel, y_vel);

                body* b = new body (m);
                b->setPosition (pos);
                b->setVelocity (vel);
                this->u.addBody (b);

            }
            /*while(Keyboard :: isKeyPressed(Keyboard :: Left))
            {
                double s = this->speed;
                printf("moving");
                this->move(-s, 0);
            }
            while(Keyboard :: isKeyPressed(Keyboard :: Right))
            {
                double s = this->speed;
                printf("moving");
                this->move(s, 0);
            }
            while(Keyboard :: isKeyPressed(Keyboard :: Up))
            {
                double s = this->speed;
                printf("moving");
                this->move(0, s);
            }
            while(Keyboard :: isKeyPressed(Keyboard :: Left))
            {
                double s = this->speed;
                printf("moving");
                this->move(0, -s);
            }*/
            while(Keyboard :: isKeyPressed(Keyboard :: Return))
                this->view = this->window->getDefaultView();
        }
    }

}
