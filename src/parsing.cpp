#include "parsing.hpp"
#include <string>
#include <iostream>

template<typename A, typename B>
Parser<B> operator >=(Parser<A> p, std::function<Parser<B>(std::string&, int)> (f))
//Parser<B> operator >=(Parser<A> p, Parser<B> (&f)(std::string&, int))
{
    if (!p.is_failed)
    {
        return f(p.str, p.to_parse);
    }
    std::cerr << "Error at " << p.to_parse << std::endl;
    auto r = Parser<B>(p.str, p.to_parse);
    r.is_failed = true;
    return r;
}

template<typename A, typename B>
Parser<B> operator >>(Parser<A> pa, Parser<B> pb)
{
    return pa >>= [=](A){return pb;};
}

template<typename A>
Parser<A> operator |(Parser<A> pa, Parser<A> pb)
{
    if (pa.is_failed)
        return pb;
    else
        return pa;
}

Parser<int> num(std::string &s, int pos)
{
    int x = 0;
    int strt = pos;
    while (pos < s.size() && '0' <= s[pos] && s[pos] <= '9')
    {
        x *= 10;
        x += s[pos] - '0';
        pos++;
    }
    if (strt == pos)
    {
        auto fail = Parser<int>(s, x, pos);
        fail.is_failed = true;
        return fail;
    }
    else
        return Parser<int>(s, x, pos);
}

/*(Parser<char>(std::string&, int)) &parse_char(char c)
{
    return [=](std::string& s, int pos)
    {
    };
}*/

typedef struct parse_char
{
    std::string c;
    parse_char()
    {
        c = ' ';
    }
    parse_char(std::string s)
    {
        c = s;
    }
    Parser<char> operator ()(std::string& s, int pos)
    {
        auto ret = Parser<char>(s, pos + 1);
        ret.data = s[pos];
        ret.is_failed = true;
        for (auto i : c) 
        {
            if (i == s[pos])
            {
                ret.data = s[pos];
                ret.is_failed = false;
                break;
            }
        }
        return ret;
    }
} parse_char;

std::function<Parser<char>(std::string&, int)> pchar(std::string c)
{
    return std::function<Parser<char>(std::string&, int)>(parse_char(c));
}

Parser<int> prod(std::string& s, int pos)
{
    std::function<Parser<int>(std::string&, int)> pnum = num;
    std::function<Parser<int>(std::string&, int)> pformula = formula;
    Parser<int> p(s, pos);
    p = pchar("(")(s, pos) >= pformula;
    auto bracket = p >= pchar(")");
    if (bracket.is_failed)
    {
        p = pnum(s, pos);
    }
    else
    {
        p.to_parse = bracket.to_parse;
    }
    int prod = p.data;
    auto op = p >= pchar("*/");
    while (!op.is_failed)
    {
        auto step = p >= pchar("*/") >= pchar("(") >= pformula;
        bracket = step >= pchar(")");
        if (bracket.is_failed)
        {
            p = p >= pnum;
        }
        else
        {
            p = step;
            p.to_parse = bracket.to_parse;
        }
        if (op.data == '*')
        {
            prod *= p.data;
        }
        else
        {
            prod /= p.data;
        }
        op = p >= pchar("*/");
    }
    p.data = prod;
    return p;
}

Parser<int> formula(std::string& s, int pos)
{
    std::function<Parser<int>(std::string&, int)> pnum = prod;
    auto p = prod(s, pos);
    int summ = p.data;
    auto op = p >= pchar("+-");
    while (!op.is_failed)
    {
        p = p >= pchar("+-") >= pnum;
        if (op.data == '+')
        {
            summ += p.data;
        }
        else
        {
            summ -= p.data;
        }
        op = p >= pchar("+-");
    }
    p.data = summ;
    return p;
}

int main(int argc, char const* argv[])
{
    std::string s;
    std::cin >> s;
    //std::function<Parser<int>(int, std::string&, int)> pars = num;
    //Parser<int> p = Parser<int>(s, 0, 0) >>= (std::function<Parser<int>(int, std::string, int)>)num<int>;
    //Parser<int> p = Parser<int>(s, 0, 0) >>= pars;
    std::function<Parser<char>(std::string&, int)> psum = pchar("+-");
    std::function<Parser<int>(std::string&, int)> pnum = num;

    auto p = formula(s, 0);
    std::cout << p.data << std::endl;

    return 0;
}
