#ifndef PARSING_H
#define PARSING_H

#include <string>
#include <functional>
#include <vector>
#include "vector2d.hpp"

// All functons return status and change calculated vector or number
// The formula syntax notation:
// <formula> ::= <sum>{<sign><sum>} | <sign><sum>{<sign><sum>}
// <sign> ::= + | -
// <sum> ::= <prod>{<op><prod>}
// <op> ::= * | /
// <prod> ::= (<formula>) | <num> | <varname>

template<class T>
struct Parser
{
    T data;
    std::string str;
    bool is_failed;
    int to_parse;
    Parser<T>(std::string &s, T v, int pos)
    {
        str = s;
        data = v;
        is_failed = false;
        to_parse = pos;
    }
    Parser<T>(std::string &s, int pos)
    {
        str = s;
        is_failed = false;
        to_parse = pos;
    }
};

using Stack = std::vector<std::string>;

Parser<Stack> formula(std::string s, int pos);
#endif

