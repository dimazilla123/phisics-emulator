#ifndef PARSING_H
#define PARSING_H

#include <string>
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

int formula (std::string s, int* analised, vector2d* vec, double* ret);
int sum (std::string s, int* analised, vector2d* vec, double* ret);
int prod (std::string s, int* analised, vector2d* vec, double* ret);

#endif

