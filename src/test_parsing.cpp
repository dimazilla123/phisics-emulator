#include <iostream>
#include "parsing.hpp"

int main(int argc, char const* argv[])
{
    std::string s;
    std::getline(std::cin, s);
    auto p = formula(s, 0);
    for (auto i : p.data) 
    {
        std::cout << i << " ";
    }
    std::cout << "\n";
    return 0;
}
