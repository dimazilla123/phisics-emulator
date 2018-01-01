#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "vector2d.hpp"
#include "body.hpp"
#include "universe.hpp"

using namespace sf;

vector2d constForce (body a, body b)
{
    double k = 0.1;
    vector2d aPos = a.getPosition();
    vector2d bPos = b.getPosition();
    return (aPos - bPos) * k;
}

vector2d gravitation (body a, body b)
{
    double G = 6.7;
    vector2d aPos = a.getPosition();
    vector2d bPos = b.getPosition();
    double m1 = a.getMass(), m2 = b.getMass();
    double r = (aPos - bPos).distance();
    return (aPos - bPos).direction() * G * m1 * m2 / (r * r);
}

int main()
{
    const int wight = 800, hight = 600;
    body b1(1), b2(2);
    b1.setPosition(vector2d(wight / 2 - 10, hight / 2 + 10));
    b2.setPosition(vector2d(wight / 2 + 10, hight / 2 - 10));

    universe u;
    u.addBody(&b1);
    u.addBody(&b2);
    u.addForce(&gravitation);

    RenderWindow window(VideoMode(wight, hight), "Graphics");

    while(window.isOpen())
    {
        Event event;
        vector<Vertex> figure;
        while(window.pollEvent(event))
        {
            while(Keyboard :: isKeyPressed(Keyboard :: Right))
            {
                vector<body*> bodies = u.getBodies();
                vector<vector2d> positions;
                for(body *b : bodies)
                {
                    vector2d posBody = b->getPosition();
                    Vector2f position(posBody.getX(), posBody.getY());
                    Vertex vert(position, Color :: Black);
                    figure.push_back(vert);
                }
                u.print(EXPORT_UNIVERSE_PRINTING_MODE);
                u.update(0.001);
                window.clear(Color :: White);
                window.draw(&figure[0], figure.size(), LineStrip);
                window.display();
            }
        }
    }

    return 0;
}

