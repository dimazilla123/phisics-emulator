#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <vector>
#include "vector2d.hpp"
#include "body.hpp"
#include <vector>

typedef vector2d (*forceFunction)(body, body);

class universe
{
    private:
        vector<body> bodies;
        vector<forceFunction> forces;
    public:
        void addBody(body b);
        void addForce(forceFunction force);
        void update(double time);
        vector<body> getBodies();
        void print();
};

#endif
