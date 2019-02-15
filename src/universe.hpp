#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <vector>
#include "vector2d.hpp"
#include "body.hpp"
#include <vector>

#define READABLE_UNIVERSE_PRINTING_MODE 0
#define EXPORT_UNIVERSE_PRINTING_MODE 1

class universe
{
    private:
        vector<body*> bodies;
        vector<forceFunction> forces;
    public:
        void addBody (body *b);
        void removeBodyByIndex (int n);
        void addForce (forceFunction force);
        void update (double time);
        vector<body*> getBodies ();
        void print (int mode);
        void move_all (vector2d offset);
};

#endif
