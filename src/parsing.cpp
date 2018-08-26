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
    //std::cerr << "Error at " << p.to_parse << std::endl;
    auto r = Parser<B>(p.str, p.to_parse);
    r.is_failed = true;
    return r;
}

template<typename A, typename B>
Parser<B> operator >>(Parser<A> pa, Parser<B> pb)
{
    std::function<Parser<B>(std::string&, int)> f = ([pb](std::string&, int) -> Parser<B>{return pb;});
    return pa >= f;
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

template<typename A>
Parser<A> operator <=(Parser<A> p, A &var)
{
    if (!p.is_failed) 
    {
        var = p.data;
    }
    return p;
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
        c = " ";
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
template<typename T>
struct change_val
{
    T v;
    change_val(T x)
    {
        v = x;
    }
    Parser<T> operator ()(std::string& s, int pos)
    {
        return Parser<T>(s, v, pos);
    }
};

template<typename T>
std::function<Parser<T>(std::string&, int)> pchange(T v)
{
    return change_val<T>(v);
}

Parser<int> prod(std::string& s, int pos)
{
    std::function<Parser<int>(std::string&, int)> pnum = num;
    std::function<Parser<int>(std::string&, int)> pformula = formula;
    int prod = 0;
    auto p = ((pchar("(")(s, pos) >= pformula <= prod >= pchar(")")) >= pchange(prod)) | ((pnum(s, pos) <= prod));
    auto op = p >= pchar("*/");
    while (!op.is_failed)
    {
        int mult = 0;
        p = ((op >= pchar("(") >= pformula) <= mult >= pchar(")") >= pchange(mult)) | (op >= pnum <= mult);
        if (op.data == '*')
        {
            prod *= mult;
        }
        else
        {
            prod /= mult;
        }
        op = p >= pchar("*/");
    }

    auto ret = Parser<int>(s, prod, p.to_parse);
    ret.is_failed = p.is_failed;
    return ret;
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
