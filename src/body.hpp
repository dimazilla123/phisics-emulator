#ifndef BODY_H
#define BODY_H

#include "vector2d.hpp"
#include <map>
#include <vector>
#include <string>
#include <functional>

class body;
using forceFunction = std::function<vector2d(const body&, const body&)>;

class body
{
    private:
        double mass;
        vector2d position;
        vector2d velocity;
        vector2d forceSum;
    public:
        std::map<std::string,double> parameters;
        body (double massN);
        void setPosition (vector2d newPos);
        vector2d getPosition () const;
        void setVelocity (vector2d newVelocity);
        vector2d getVelocity () const;
        body (double massN, std::vector<std::string> parametersNames);
        void setParameter (std::string name, double value);
        double getParameter (std::string name) const;
        double getMass () const;
        void setMass (double m);
        void move (double dt);
        void applicateForce (body &other, forceFunction);

};

#endif
