#include <QApplication>
#include <fstream>
#include "vector2d.hpp"
#include "body.hpp"
#include "universe.hpp"
#include "interface.hpp"
#include "parsing.hpp"
#include "semantics.hpp"

vector2d constForce (const body& a, const body& b)
{
    double k = 20;
    vector2d aPos = a.getPosition ();
    vector2d bPos = b.getPosition ();
    return (bPos - aPos).direction () * k;
}

vector2d goock_force (const body& a, const body& b)
{
    double k = 80;
    vector2d aPos = a.getPosition ();
    vector2d bPos = b.getPosition ();
    return (bPos - aPos) * k;
}

vector2d gravitation(const body& a, const body& b)
{
    double G = 1;
    vector2d aPos = a.getPosition();
    vector2d bPos = b.getPosition();
    double m1 = a.getMass(), m2 = b.getMass();
    double r = (aPos - bPos).distance ();
    return (bPos - aPos).direction () * G * m1 * m2 / (r * r);
}

int main(int argc, char** argv)
{
    int wight = 600, hight = 400;
    double time = 0.001, speed = 1;

    if (argc < 2) 
    {
        fprintf(stderr, "Usage: %s [FORCELIST]\n", argv[0]);
        return 0;
    }
    std::fstream force_file(argv[1], force_file.in);

    universe u;
    u.addForce (&goock_force);
    std::string force_line;
    while (std::getline(force_file, force_line)) 
    {
        Parser<Stack> form = formula(force_line, 0);
        if (form.is_failed) 
        {
            fprintf(stderr, "Cannot parse %s", force_line.c_str());
            continue;
        }
        u.addForce(createFuncFromCalc(form.data));
    }

    QApplication app(argc, argv);

    interface interf(u, wight, hight, speed);
    interf.show();
    interf.run(time);

    app.exec ();

    return 0;
}

