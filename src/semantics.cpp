#include "semantics.hpp"
#include <cstdio>
#include <sstream>
#include <map>
#include <vector>

using std::pair;

std::vector<token> prepare(Stack& expr, body b1, body b2)
{
    body bodies[] = {b1, b2};
    std::vector<token> ret;
    for (auto s : expr) 
    {
        token obj;
        if (s == "+" || s == "-" || s == "*" || s == "/" || s == "%")
        {
            obj.op = s[0];
            obj.t = op;
        }
        else
        {
            std::string name;
            std::istringstream inp(s);
            int n = 1;
            std::getline(inp, name, '_');
            inp >> n;
            n--;

            auto found = bodies[n].parameters.find(name);
            if (found != bodies[n].parameters.end())
            {
                obj.n = (*found).second;
                obj.t = num;
            }
            else
            {
                obj.t = vec;
                if (name[0] == 'v')
                {
                    obj.v = bodies[n].getVelocity();
                }
                else if (name[0] == 'r')
                {
                    obj.v = bodies[n].getPosition();
                }
                else
                {
                    obj.t = num;
                    obj.n = std::atoi(s.data());
                }
            }
        }
        ret.push_back(obj);
    }
    return ret;
}

token calc(Stack& expr, body b1, body b2)
{
    vector2d r;
    std::vector<token> st;
    auto data = prepare(expr, b1, b2);
    for (auto t : data) 
    {
        if (t.t != op)
        {
            st.push_back(t);
        }
        else
        {
            token op2 = st.back();
            st.pop_back();
            token op1 = st.back();
            st.pop_back();
            token r;
            if (op2.t == op1.t)
            {
                if (op1.t == num)
                {
                    r.t = num;
                    if (t.op == '+')
                    {
                        r.n = op1.n + op2.n;
                    }
                    if (t.op == '-')
                    {
                        r.n = op1.n - op2.n;
                    }
                    if (t.op == '*')
                    {
                        r.n = op1.n * op2.n;
                    }
                    if (t.op == '/')
                    {
                        r.n = op1.n / op2.n;
                    }
                }
                if (op1.t == vec)
                {
                    if (t.op == '+')
                    {
                        r.t = vec;
                        r.v = op1.v + op2.v;
                    }
                    if (t.op == '-')
                    {
                        r.t = vec;
                        r.v = op1.v - op2.v;
                    }
                    if (t.op == '*')
                    {
                        r.t = num;
                        r.n = op2.v * op2.v;
                    }
                    if (t.op == '%')
                    {
                        r.t = num;
                        r.n = op1.v % op2.v;
                    }
                }
            }
            else
            {
                r.t = vec;
                if (op1.t == vec)
                {
                    std::swap(op1, op2);
                }
                if (t.op == '*')
                {
                    r.v = op2.v * op1.n;
                }
            }
            st.push_back(r);
        }
    }
    return st[0];
}
