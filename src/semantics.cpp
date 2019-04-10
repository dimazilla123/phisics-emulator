#include "semantics.hpp"
#include <cstdio>
#include <sstream>
#include <map>
#include <vector>

using std::pair;

bool is_num(const std::string& s)
{
    for (auto c : s)
        if (!(('0' <= c && c <= '9') || c == '.'))
            return false;
    return true;
}

std::vector<token> prepare(const Stack& expr, body b1, body b2)
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
        else if (is_num(s))
        {
            obj.n = std::stod(s);
            obj.t = num;
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

token calc(const Stack& expr, const body& b1, const body& b2)
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

struct force_str
{
    Stack expr;
    force_str(const Stack& e) : expr(e) {}
    vector2d operator()(const body& a, const body& b)
    {
        auto res = calc(expr, a, b);
        if (res.t == vec)
            return res.v;
        else
        {
            fprintf(stderr, "Error!\n");
            return vector2d();
        }
    }
};

forceFunction createFuncFromCalc(Stack& expr)
{
    return force_str(expr);
    return [expr](const body& a, const body& b)
    {
        static auto res = calc(expr, a, b);
        if (res.t == vec)
            return res.v;
        else
        {
            fprintf(stderr, "Error!\n");
            return vector2d();
        }
    };
}
