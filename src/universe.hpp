#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <vector>
#include "vector2d.hpp"
#include "body.hpp"
#include <vector>

#define READABLE_UNIVERSE_PRINTING_MODE 0
#define EXPORT_UNIVERSE_PRINTING_MODE 1

class Universe
{
    public:
        void clean();
        std::vector<Body> bodies;
        std::vector<std::string> forcename;
        std::vector<forceFunction> forces;
        void addBody(const Body& b);
        void removeBodyByIndex(int n);
        void addForce(forceFunction force);
        void removeForce();
        void addForce(forceFunction force, const std::string& name);
        void update(double time);
        std::vector<Body> getBodies();
        void print(int mode);
        void moveAll(vector2d offset);
        void save(const std::string& filename);
        bool load(const std::string& filename); // false if failed
};

#endif
