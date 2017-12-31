#ifndef BODY_H
#define BODY_H

#include "vector2d.hpp"
#include <map>
#include <vector>

class body
{
    private:
        double mass;
        vector2d position;
        vector2d velocity;
        vector2d forceSum;
        //map<string,double> parameters;
    public:
        body(double massN);
        void setPosition(vector2d newPos);
        vector2d getPosition();
        void setVelocity(vector2d newVelocity);
        vector2d getVelocity();
        //body(double massN, vector<string> parametersNames);
        void move(double dt);
        //void applicateForce(body other);
};

#endif
