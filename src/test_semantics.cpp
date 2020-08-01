#include "semantics.hpp"
#include <iostream>

int main(int argc, char const* argv[])
{
    std::string s;
    std::getline(cin, s);
    auto p = formula(s, 0);
    Body b1(1), b2(1);
    b1.setPosition({100, 100});
    b2.setPosition({100, 200});

    auto prep = calc(p.data, b1, b2);
    if (prep.t == TokenType::NUM)
    {
        std::cout << prep.n << std::endl;
    }
    else
    {
        std::cout << prep.v.getX() << " " << prep.v.getY() << std::endl;
    }
    auto f = createFuncFromCalc(p.data);
    vector2d res = f(b1, b2);
    std::cout << res.getX() << " " << res.getY() << "\n";

    return 0;
}
