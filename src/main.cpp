#include <QApplication>
#include <fstream>
#include "vector2d.hpp"
#include "body.hpp"
#include "universe.hpp"
#include "interface.hpp"
#include "parsing.hpp"
#include "semantics.hpp"

vector2d constForce(const Body& a, const Body& b)
{
    double k = 20;
    vector2d aPos = a.getPosition();
    vector2d bPos = b.getPosition();
    return (bPos - aPos).direction() * k;
}

vector2d goock_force(const Body& a, const Body& b)
{
    double k = 80;
    vector2d aPos = a.getPosition();
    vector2d bPos = b.getPosition();
    return (bPos - aPos) * k;
}

vector2d gravitation(const Body& a, const Body& b)
{
    double G = 40000;
    vector2d aPos = a.getPosition();
    vector2d bPos = b.getPosition();
    double m1 = a.getMass(), m2 = b.getMass();
    double r = (aPos - bPos).distance();
    return (bPos - aPos).direction() * G * m1 * m2 / (r * r);
}

int main(int argc, char** argv)
{
    int wight = 600, hight = 400;
    double time = 0.001, speed = 1;
    Universe u;
    //u.addForce(gravitation);
    //u.addForce(goock_force);

    if (argc < 2) 
    {
        fprintf(stderr, "Usage: %s [FORCELIST]\n", argv[0]);
        fprintf(stderr, "No force file\n");
        
    }
    else
    {
        std::ifstream force_file(argv[1]);
        std::string force_line;
        while (std::getline(force_file, force_line)) 
        {
            std::cout << force_line << "\n";
            Parser<Stack> form = formula(force_line, 0);
            if (form.is_failed) 
            {
                fprintf(stderr, "Cannot parse %s", force_line.c_str());
                continue;
            }
            u.addForce(createFuncFromCalc(form.data), force_line);
        }
    }

    /*
    Body b1(1), b2(1);
    b1.setPosition(vector2d(100, 100));
    b2.setPosition(vector2d(200, 100));
    u.addBody(&b1);
    u.addBody(&b2);
    u.addForce(&goock_force);
    */
    

    QApplication app(argc, argv);

    Interface interf(u, wight, hight, speed);
    interf.show();
    interf.run(time);

    app.exec();

    return 0;
}

