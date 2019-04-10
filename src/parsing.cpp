#include "parsing.hpp"
#include <string>
#include <iostream>
#include <cassert>

/*! \enum LexemType
 *
 *  Detailed description
 */
enum LexemType
{ 
    NUMBER,
    NAME,
    OPERATION,
    BRAKET,
    NONE
};

struct Lexem
{
    LexemType type;
    std::string s;
};

Parser<Lexem> get_lexem(Parser<Lexem> prev)
{
    std::string& s = prev.str;
    Parser<Lexem> ret(s, {NONE, ""}, prev.to_parse);
    int& pos = ret.to_parse;
    ret.is_failed = true;
    if (pos >= s.size()) 
        return ret;
    if (s[pos] == '(' || s[pos] == ')') 
    {
        ret.data.type = LexemType::BRAKET;
        ret.data.s = s[pos];
        ret.is_failed = false;
        ++ret.to_parse;
    } else if (s[pos] == '+' || s[pos] == '-'
            || s[pos] == '*' || s[pos] == '/' || s[pos] == '%')
    {
        ret.data.type = LexemType::OPERATION;
        ret.data.s = s[pos];
        ret.is_failed = false;
        ++ret.to_parse;
    } else if (('0' <= s[pos] && s[pos] <= '9') || s[pos] == '.') 
    {
        ret.is_failed = false;
        ret.data.type = LexemType::NUMBER;
        while (('0' <= s[pos] && s[pos] <= '9') || s[pos] == '.')
        {
            ret.data.s += s[pos];
            ++pos;
        }
    } else if (('a' <= s[pos] && s[pos] <= 'z') || s[pos] == '_') 
    {
        ret.is_failed = false;
        ret.data.type = LexemType::NAME;
        while (('a' <= s[pos] && s[pos] <= 'z') || s[pos] == '_' || (('0' <= s[pos] && s[pos] <= '9') || s[pos] == '.'))
        {
            ret.data.s += s[pos];
            ++pos;
        }
    }
    return ret;
}

Parser<Stack> formula(std::string& s, int pos)
{
    std::cerr << "formula(" << s << ", " << pos << ")" << std::endl;
    Parser<Stack> ret(s, 0);

    std::vector<Lexem> st;
    Parser<Lexem> lex = get_lexem(Parser<Lexem>(s, {NONE, ""}, 0));
    while (!lex.is_failed) 
    {
        if (lex.data.type == LexemType::NUMBER || lex.data.type == LexemType::NAME) 
            ret.data.push_back(lex.data.s);
        else if (lex.data.type == LexemType::BRAKET)
        {
            if (lex.data.s == "(") 
                st.push_back(lex.data);
            else
            {
                assert(st.size() >= 1);
                while (st.back().s != "(") 
                {
                    ret.data.push_back(st.back().s);
                    st.pop_back();
                }
                st.pop_back();
            }
        } else if (lex.data.type == LexemType::OPERATION) 
        {
            auto get_prior = [](const std::string& s) { return s == "+" || s == "-" ? 0 : 1; };
            while (!st.empty() && st.back().type == LexemType::OPERATION && get_prior(st.back().s) > get_prior(lex.data.s))
            {
                ret.data.push_back(st.back().s);
                st.pop_back();
            }
            st.push_back(lex.data);
        }
        lex = get_lexem(lex);
    }
    while (!st.empty()) 
    {
        ret.data.push_back(st.back().s);
        st.pop_back();
    }

    return ret;
}
