#include "universe.hpp"
#include "parsing.hpp"
#include "semantics.hpp"

#include <iostream>
#include <fstream>

void Universe::clean()
{
    forcename.clear();
    forces.clear();
    bodies.clear();
}

void Universe::addBody(const Body& b)
{
    this->bodies.push_back(b);
}

void Universe::removeBodyByIndex(int n)
{
    this->bodies.erase(this->bodies.begin() + n);
}

void Universe::addForce(forceFunction f)
{
    addForce(f, "unnamed");
}

void Universe::removeForce()
{
    this->forces.pop_back();
}

void Universe::addForce(forceFunction f, const std::string& name)
{
    this->forces.push_back(f);
    this->forcename.push_back(name);
}

void Universe::update(double time)
{
    for (forceFunction f : forces) {
        for (int i = 0; i < bodies.size(); i++) {
            for (int j = 0; j < bodies.size(); j++) {
                if (i != j) {
                    bodies[i].applicateForce(bodies[j], f);
                }
            }
        }
    }
    for (Body& a : this->bodies)
        a.move(time);
}

std::vector<Body> Universe::getBodies()
{
    return this->bodies;
}

void Universe::print(int mode)
{
    for (Body& b : this->bodies)
    {
        vector2d pos = b.getPosition();
        vector2d vel = b.getVelocity();
        if (mode == READABLE_UNIVERSE_PRINTING_MODE)
        {
            printf("position %lf %lf\n", pos.getX(), pos.getY());
            printf("velocity %lf %lf\n", vel.getX(), vel.getY());
            getchar();
        }
        if (mode == EXPORT_UNIVERSE_PRINTING_MODE)
        {
            printf("%lf %lf ", pos.getX(), pos.getY());
            printf("%lf %lf ", vel.getX(), vel.getY());
        }
    }
    putchar('\n');
}

void Universe::moveAll(vector2d offset)
{
    for (auto &b : bodies)
    {
        vector2d cur_pos = b.getPosition();
        b.setPosition(cur_pos + offset);
    }
}

void Universe::save(const std::string& filename)
{
    std::ofstream out(filename);
    out << bodies.size() << "\n";
    for (Body& b : bodies) {
        out << b.getMass() << "\n";
        out << b.parameters.size() << "\n";
        for (auto [name, val] : b.parameters)
            out << name << " " << val << "\n";
        out << b.getPosition().getX() << " " << b.getPosition().getY() << "\n";
        out << b.getVelocity().getX() << " " << b.getVelocity().getY() << "\n";
    }
    out << forces.size() << "\n";
    for (std::string s : forcename)
        out << s << "\n";
}

bool Universe::load(const std::string& filename)
{
    std::ifstream in(filename);
    bool res = true;
    int n = 0;
    if (!(in >> n))
        res = false;
    for (int i = 0; i < n; i++) {
        double m;
        if (in >> m) {
            bodies.push_back(Body(m));
            int param_cnt = 0;
            if (in >> param_cnt) {
                for (int j = 0; j < param_cnt; j++) {
                    std::string name; double val;
                    in >> name >> val;
                    bodies.back().parameters[name] = val;
                }
            } else return false;
            double posx, posy, velx, vely;
            if (in >> posx >> posy >> velx >> vely) {
                bodies.back().setPosition(vector2d(posx, posy));
                bodies.back().setVelocity(vector2d(velx, vely));
            } else return false;
        } else return false;
    }
    int forces_cnt;
    if (in >> forces_cnt) {
        std::string force_Str;
        std::getline(in, force_Str);
        for (int i = 0; i < forces_cnt; i++) {
            if (std::getline(in, force_Str)) {
                Parser<Stack> form = formula(force_Str, 0);
                if (!form.is_failed)
                    addForce(createFuncFromCalc(form.data), force_Str);
            } else return false;
        }
    }
    return res;
}
