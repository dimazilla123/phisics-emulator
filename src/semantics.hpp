#ifndef SEMANTICS_H
#define SEMANTICS_H

#include "parsing.hpp"
#include "body.hpp"
#include "vector2d.hpp"
#include <functional>

enum TokenType
{
    NUM,
    VEC,
    OP,
    FUNCTION
};
struct token
{
    TokenType t;
    double n;
    char op;
    vector2d v;
    std::string func;
};

token calc(const Stack& expr, const Body& a, const Body& b);
std::vector<token> prepare(Stack& expr, Body b1, Body b2);

forceFunction createFuncFromCalc(Stack& expr);

#endif
