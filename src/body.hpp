#ifndef BODY_H
#define BODY_H

#include "vector2d.hpp"
#include <map>
#include <vector>
#include <string>
#include <functional>

class body;
using forceFunction = std::function<vector2d(const body&, const body&)>;
using namespace std;

class body
{
    private:
        double mass;
        vector2d position;
        vector2d velocity;
        vector2d forceSum;
    public:
        map<string,double> parameters;
        body (double massN);
        void setPosition (vector2d newPos);
        vector2d getPosition () const;
        void setVelocity (vector2d newVelocity);
        vector2d getVelocity () const;
        body (double massN, vector<string> parametersNames);
        void setParameter (string name, double value);
        double getParameter (string name) const;
        double getMass () const;
        void setMass (double m);
        void move (double dt);
        void applicateForce (body &other, forceFunction);

};

#endif
