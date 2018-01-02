#include "interface.hpp"

using namespace sf;

interface :: interface(universe vers, int w, int h, int s)
{
    this->u = vers;
    this->speed = s;
    this->window = new RenderWindow(VideoMode(w,h), "interface");
    this->window->setView(View(FloatRect(0, 0, w, h)));
}

void interface :: move(int x, int y)
{
    View v = this->window->getView();
    v.move(x,y);
    this->window->setView(v);
}

void interface :: run(double time)
{
    while(this->window->isOpen())
    {
        Event event;
        vector<Vertex> figure;
        while(this->window->pollEvent(event))
        {
            while(Keyboard :: isKeyPressed(Keyboard :: Space))
            {
                vector<body*> bodies = this->u.getBodies();
                for(body *b : bodies)
                {
                    vector2d posBody = b->getPosition();
                    Vector2f position(posBody.getX(), posBody.getY());
                    Vertex vert(position, Color :: Black);
                    figure.push_back(vert);
                }
                figure.push_back(figure[0]);
                //u.print(EXPORT_UNIVERSE_PRINTING_MODE);
                u.update(time);
                this->window->clear(Color :: White);
                this->window->draw(&figure[0], figure.size(), LineStrip);
                this->window->display();
                figure.clear();
            }
            while(Keyboard :: isKeyPressed(Keyboard :: Left))
            {
                int s = this->speed;
                this->move(-s, 0);
            }
            while(Keyboard :: isKeyPressed(Keyboard :: Right))
            {
                int s = this->speed;
                this->move(s, 0);
            }
            while(Keyboard :: isKeyPressed(Keyboard :: Up))
            {
                int s = this->speed;
                this->move(0, s);
            }
            while(Keyboard :: isKeyPressed(Keyboard :: Left))
            {
                int s = this->speed;
                this->move(0, -s);
            }
        }
    }

}
