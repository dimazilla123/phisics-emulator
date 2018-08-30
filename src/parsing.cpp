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
Parser<B> operator >=(Parser<A> p, Parser<B> (&f)(std::string&, int))
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
    if (!pa.is_failed)
        return pa;
    else
        return pb;
}

/*Parser<void> end_parse(std::string &s, int pos)
{
    return Parser<void>(s, pos);
}*/

Parser<Stack> num(std::string &s, int pos)
{
    std::string str = "";
    while (pos < s.size() && '0' <= s[pos] && s[pos] <= '9')
    {
        str.push_back(s[pos]);
        pos++;
    }
    auto p = Parser<Stack>(s, Stack({str}), pos);
    p.is_failed = str.empty();
    return p;
}

Parser<Stack> name(std::string &s, int pos)
{
    std::string str = "";
    while (pos < s.size() && 'a' <= s[pos] && s[pos] <= 'z')
    {
        str.push_back(s[pos]);
        pos++;
    }
    auto tmp = pchar("_")(s, pos) >= pchar("12");
    auto p = Parser<Stack>(s, Stack({str + "_" + tmp.data}), tmp.to_parse);
    return p;
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
template<class T>
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

Parser<Stack> prod(std::string& s, int pos)
{
    std::cerr << "prod(" << s << ", " << pos << ")" << std::endl;
    Stack tmp;
    auto p = 
             (pchar("(")(s, pos) >= formula <= tmp >= pchar(")") >= pchange(tmp)) |
             num(s, pos)  | 
             name(s, pos);
    if (!p.is_failed)
    {
        std::cerr << "Tmp";
        for (auto &i : p.data) 
        {
            std::cerr << " " << i;
        }
        std::cerr << std::endl;
    }
    return p;
}

Parser<Stack> summ(std::string& s, int pos)
{
    std::cerr << "summ(" << s << ", " << pos << ")" << std::endl;
    //std::function<Parser<Stack&>(std::string&, int)> pprod = prod;
    Stack left, right;
    char op = ' ';
    auto p = (prod(s, pos) <= left >= pchar("*/%") <= op >= summ <= right) |
             (prod(s, pos) <= left);
    p.data = left;
    p.data.insert(p.data.end(), right.begin(), right.end());
    if (op != ' ')
    {
        std::string str = "";
        str.push_back(op);
        p.data.push_back(str);
    }
    if (!p.is_failed)
    {
        std::cerr << "Tmp ";
        for (auto &i : p.data) 
        {
            std::cerr << i << " ";
        }
        std::cerr << std::endl;
    }
    return p;
}

Parser<Stack> formula(std::string& s, int pos)
{
    std::cerr << "formula(" << s << ", " << pos << ")" << std::endl;
    //std::function<Parser<Stack&>(std::string&, int)> pprod = prod;
    Stack left, right;
    char op = ' ';
    auto p = (summ(s, pos) <= left >= pchar("+-") <= op >= formula <= right) |
             (summ(s, pos) <= left);
    p.data = left;
    p.data.insert(p.data.end(), right.begin(), right.end());
    if (op != ' ')
    {
        std::string str = "";
        str.push_back(op);
        p.data.push_back(str);
    }
    if (!p.is_failed)
    {
        std::cerr << "Tmp ";
        for (auto &i : p.data) 
        {
            std::cerr << i << " ";
        }
        std::cerr << std::endl;
    }
    return p;
}
