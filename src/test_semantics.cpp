#include "semantics.hpp"
#include <iostream>

int main(int argc, char const* argv[])
{
    std::string s;
    std::cin >> s;
    auto p = formula(s, 0);
    body b1(1), b2(1);

    auto prep = calc(p.data, b1, b2);
    return 0;
}
