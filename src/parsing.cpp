#include "parsing.hpp"
#include <string>
#include <iostream>

template<typename A, typename B>
Parser<B> operator >>=(Parser<A> p, std::function<Parser<B>(A, std::string&, int)> f)
{
    if (!p.is_failed)
    {
        return f(p.data);
    }
    else
    {
        auto r = Parser<B>(p.str, p.pos);
        r.is_failed = true;
        return r;
    }
}

template<typename A, typename B>
Parser<B> operator >>(Parser<A> pa, Parser<B> pb)
{
    return pa >>= [=](A){return pb;};
}

template<typename A>
Parser<int> num(A, std::string s, int pos)
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

int main(int argc, char const* argv[])
{
    std::string s;
    std::cin >> s;
    Parser<int> p = Parser<int>(s, 0, 0) >>= num;
    return 0;
}
