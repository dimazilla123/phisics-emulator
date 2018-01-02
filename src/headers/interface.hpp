#ifndef INTERFACE_H
#define INTERFACE_H

#include <SFML/Graphics.hpp>
#include "universe.hpp"

class interface
{
    private:
        sf :: RenderWindow* window;
        int h, w;
        universe u;
        int speed;
    public:
        interface(universe vers, int w, int h, int speed);
        //void setSize(int x, int y);
        void move(int x, int y);
        void run(double time);
};

#endif
