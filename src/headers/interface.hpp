#ifndef INTERFACE_H
#define INTERFACE_H

#include <SFML/Graphics.hpp>
#include "universe.hpp"

class interface
{
    private:
        sf :: RenderWindow* window;
        sf :: View view;
        int h, w;
        universe u;
        double speed;
    public:
        interface(universe vers, int w, int h, double speed);
        //void setSize(int x, int y);
        void move(int x, int y);
        void run(double time);
};

#endif
