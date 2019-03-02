#ifndef SEMANTICS_H
#define SEMANTICS_H

#include "parsing.hpp"
#include "body.hpp"
#include "vector2d.hpp"
#include <functional>

enum type
{
    num,
    vec,
    op
};
struct token
{
    type t;
    double n;
    char op;
    vector2d v;
};

token calc(const Stack& expr, const body& a, const body& b);
std::vector<token> prepare(Stack& expr, body b1, body b2);

forceFunction createFuncFromCalc(Stack& expr);

#endif
