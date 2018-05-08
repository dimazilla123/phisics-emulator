#include "parsing.hpp"
#include <string>
#include <iostream>

int formula (std::string s, int* analised, vector2d* vec, double* ret)
{
    if (*analised < s.size ())
    {
        int sign;
        if (s[*analised] == '+')
        {
            sign = 1;
            ++*(analised);
        }
        else if (s[*analised] == '-')
        {
            ++*(analised);
            sign = -1;
        }
        int status = sum (s, analised, vec, ret);
        if (status == PARSE_FAIL)
        {
            std::cout << "Parse error: sum expected at " << *analised << std::endl;
            return PARSE_FAIL;
        }
        else
        {
            int next_status;
            while (*analised < s.size ())
            {
                vector2d* next_vec = new vector2d ();
                double* next_ret = new double;
                sign = 1;
                if (s[*analised] == '-')
                    sign = -1;
                else if (s[*analised] != '+')
                {
                    std::cout << "Sign expected at " << *analised << std::endl;
                    return PARSE_FAIL;
                }
                ++*(analised);
                next_status = sum (s, analised, next_vec, next_ret);
                if (next_status != status)
                {
                    std::cout << "Type sum error at " << *analised << std::endl;
                    return PARSE_FAIL;
                }
                else if (next_status == PARSE_VECTOR)
                {
                    *(vec) += *(next_vec) * sign;
                }
                else
                {
                    *(ret) += *(next_ret) * sign;
                }
            }
        }
    }
}

int sum (std::string s, int* analised, vector2d* vec, double* ret)
{
    int x = 0;
    while ('0' <= s[*analised] && s[*analised] <= '9')
    {
        x *= 10;
        x += s[*analised] - '0';
        ++*(analised);
    }
    *(ret) = x;
    return PARSE_NUM;
}
