#include "semantics.hpp"
#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <cmath>

using std::pair;

bool is_num(const std::string& s)
{
    for (auto c : s)
        if (!(('0' <= c && c <= '9') || c == '.'))
            return false;
    return true;
}

std::vector<Token> prepare(const Stack& expr, Body b1, Body b2)
{
    Body bodies[] = {b1, b2};
    std::vector<Token> ret;
    for (auto s : expr) 
    {
        Token obj;
        if (s == "+" || s == "-" || s == "*" || s == "/" || s == "%" || s == "^")
        {
            obj.op = s[0];
            obj.t = TokenType::OP;
        }
        else if (is_num(s))
        {
            obj.n = std::stod(s);
            obj.t = TokenType::NUM;
        }
        else if (s == "abs")
        {
            obj.t = TokenType::FUNCTION;
            obj.func = s;
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
                obj.t = TokenType::NUM;
            }
            else if (name == "m")
            {
                obj.n = bodies[n].getMass();
                obj.t = TokenType::NUM;
            }
            else
            {
                obj.t = TokenType::VEC;
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
                    obj.t = TokenType::NUM;
                    obj.n = std::atoi(s.data());
                }
            }
        }
        ret.push_back(obj);
    }
    return ret;
}

void print_Token_st(const std::vector<Token>& v)
{
    for (auto t : v) {
        if (t.t == TokenType::NUM)
            std::cerr << t.n << " ";
        else if (t.t == TokenType::OP)
            std::cerr << t.op << " ";
        else if (t.t == TokenType::VEC)
            std::cerr << "(" << t.v.getX() << " " << t.v.getY() << ") ";
        else if (t.t == TokenType::FUNCTION)
            std::cerr << t.func << " ";
    }
    std::cerr << "\n";
}

Token calc(const Stack& expr, const Body& b1, const Body& b2)
{
    vector2d r;
    std::vector<Token> st;
    auto data = prepare(expr, b1, b2);
    for (auto t : data) 
    {
        if (t.t == TokenType::VEC || t.t == TokenType::NUM)
        {
            st.push_back(t);
        }
        else if (t.t == TokenType::FUNCTION)
        {
            Token operand = st.back();
            st.pop_back();
            Token r;
            r.t = TokenType::NUM;
            if (operand.t == TokenType::NUM)
                r.n = std::abs(operand.n);
            else if (operand.t == TokenType::VEC)
                r.n = operand.v.distance();
            st.push_back(r);
        }
        else
        {
            Token op2 = st.back();
            st.pop_back();
            Token op1 = st.back();
            st.pop_back();
            Token r;
            if (op2.t == op1.t)
            {
                if (op1.t == TokenType::NUM)
                {
                    r.t = TokenType::NUM;
                    if (t.op == '+')
                        r.n = op1.n + op2.n;
                    if (t.op == '-')
                        r.n = op1.n - op2.n;
                    if (t.op == '*')
                        r.n = op1.n * op2.n;
                    if (t.op == '/')
                        r.n = op1.n / op2.n;
                    if (t.op == '^')
                        r.n = std::pow(op1.n, op2.n);
                }
                if (op1.t == TokenType::VEC)
                {
                    if (t.op == '+')
                    {
                        r.t = TokenType::VEC;
                        r.v = op1.v + op2.v;
                    }
                    if (t.op == '-')
                    {
                        r.t = TokenType::VEC;
                        r.v = op1.v - op2.v;
                    }
                    if (t.op == '*')
                    {
                        r.t = TokenType::NUM;
                        r.n = op2.v * op2.v;
                    }
                    if (t.op == '%')
                    {
                        r.t = TokenType::NUM;
                        r.n = op1.v % op2.v;
                    }
                }
            }
            else
            {
                r.t = TokenType::VEC;
                if (op1.t == TokenType::VEC)
                {
                    std::swap(op1, op2);
                }
                if (t.op == '*')
                {
                    r.v = op2.v * op1.n;
                }
                else if (t.op == '/')
                {
                    r.v = op2.v / op1.n;
                }
            }
            st.push_back(r);
        }
        //print_Token_st(st);
    }
    return st[0];
}

struct force_str
{
    Stack expr;
    force_str(const Stack& e) : expr(e) {}
    vector2d operator()(const Body& a, const Body& b)
    {
        auto res = calc(expr, a, b);
        if (res.t == TokenType::VEC)
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
    return [expr](const Body& a, const Body& b)
    {
        static auto res = calc(expr, a, b);
        if (res.t == TokenType::VEC)
            return res.v;
        else
        {
            fprintf(stderr, "Error!\n");
            return vector2d();
        }
    };
}
