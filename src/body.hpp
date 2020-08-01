#ifndef BODY_H
#define BODY_H

#include "vector2d.hpp"
#include <map>
#include <vector>
#include <string>
#include <functional>

class Body;
using forceFunction = std::function<vector2d(const Body&, const Body&)>;

class Body
{
    private:
        double mass;
        vector2d position;
        vector2d velocity;
        vector2d forceSum;
    public:
        std::map<std::string, double> parameters;
        Body(double massN);
        void setPosition(vector2d newPos);
        vector2d getPosition() const;
        void setVelocity(vector2d newVelocity);
        vector2d getVelocity() const;
        Body(double massN, std::vector<std::string> parametersNames);
        void setParameter(std::string name, double value);
        double getParameter(std::string name) const;
        double getMass() const;
        void setMass(double m);
        void move(double dt);
        void applicateForce(Body &other, forceFunction);

};

#endif
