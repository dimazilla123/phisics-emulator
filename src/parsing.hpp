#ifndef PARSING_H
#define PARSING_H

#include <string>
#include <functional>
#include "vector2d.hpp"

#define PARSE_VECTOR 0
#define PARSE_NUM 1
#define PARSE_FAIL 2

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

template<typename A, typename B>
//Parser<B> operator >=(Parser<A> p, Parser<B> &f(std::string&, int));
Parser<B> operator >=(Parser<A>, std::function<Parser<B>(std::string&, int)>);

template<typename A, typename B>
Parser<B> operator >>(Parser<A>, Parser<B>);

Parser<int> formula(std::string& s, int pos);
/*
int formula (std::string s, int* analised, vector2d* vec, double* ret);
int sum (std::string s, int* analised, vector2d* vec, double* ret);
int prod (std::string s, int* analised, vector2d* vec, double* ret);
int num (std::string s, int* analised, vector2d* vec, double* ret);
*/

#endif

