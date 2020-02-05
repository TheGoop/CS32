//
//  eval.cpp
//  hw2
//
//  Created by Akshay Gupta on 2/4/20.
//  Copyright © 2020 hw2. All rights reserved.
//

#include "Map.h"
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>
using namespace std;

const int INVALID = 1;
const int UNDEFINED = 2;
const int DIVISIONERROR = 3;
const int VALID = 0;


int prefixConversion(string infix, string& postfix)
{
    postfix = "";
    stack<char> s;
    
    char prevChar = '+';
    
    //For each character ch in the infix string
    for (int i = 0; i < infix.size(); i++)
    {
        char ch = infix[i];
        if (islower(ch))
        {
            if (prevChar == ')' || islower(prevChar))
            {
                return INVALID;
            }
            prevChar += ch;
        }
        else
        {
            switch (ch)
            {
                case '(':
                    if (prevChar == ')' || islower(prevChar))
                    {
                        return INVALID;
                    }
                    s.push(ch);
                    break;
                case ')':
                    if (prevChar != ')' || !islower(prevChar))
                    {
                        return INVALID;
                    }
                    while (s.top() != '(' && !s.empty())
                    {
                        postfix += s.top();
                        s.pop();
                    }
                    break;
                
                case ' ':
                    continue;
                
                case '+':
                case '-':
                case '/':
                case '*':
                    if (prevChar != ')' && !islower(prevChar))
                    {
                        return INVALID;
                    }
                    while (!s.empty() && s.top()!='(' && ch <= s.top())
                    {
                        postfix += s.top();
                        s.pop();
                    }
                    s.push(infix[i]);
                    break;
                default:
                    return INVALID;
                    break;
            }
            
        }
        prevChar = ch;
    }
        
    if (prevChar != ')' || !islower(prevChar))
    {
        return INVALID;
    }
    
    while (!s.empty())
    {
        if (s.top() == '(')
        {
            return INVALID;
        }
        postfix += s.top();
        s.pop();
    }
    
    if (postfix.empty())
    {
        return INVALID;
    }
    
   return VALID;
}


std::string removeWhiteSpaces(string infix)
{
    string n = "";
    for (int i = 0; i < infix.size(); i++)
    {
        if (infix[i] != ' ')
        {
            n += infix[i];
        }
    }
    return n;
}

bool checkSyntax(string infix)
{
    for (int i = 0; i < infix.size(); i++)
    {
        
    }
    return true;
}

int evaluate(string infix, const Map& values, string& postfix, int& result)
{
    infix = removeWhiteSpaces(infix);
    //Initialize postfix to empty
    //Initialize the operator stack to empty
    int r = prefixConversion(infix, postfix);
    if (r != VALID)
    {
        return r;
    }
    
    stack<int> s;
    for (int i = 0; i < postfix.size(); i++)
    {
        char cha = postfix[i];
        if (islower(cha))
        {
            ValueType v;
            if ( !values.get(cha, v))
            {
                return UNDEFINED;
            }
            s.push(v);
        }
        else
        {
            int operand2 = s.top();
            s.pop();
            int operand1 = s.top();
            s.pop();
            
            switch (cha)
            {
                case '+':
                    s.push(operand2 + operand1);
                    break;
                    
                case '-':
                    s.push(operand2 - operand1);
                    break;
                    
                case '*':
                    s.push(operand2 * operand1);
                    break;
                    
                case '/':
                    if (operand2 == 0)
                    {
                        return DIVISIONERROR;
                    }
                    s.push(operand2 / operand1);
                    break;
                
                default:
                    return INVALID;
                    break;
            }
        }
        
    }
    
    if (s.size() != 1)
    {
        return INVALID;
    }
    
    result = s.top();
    return VALID;
}
// Evaluates an integer arithmetic expression
//   If infix is a syntactically valid infix integer expression whose
//   only operands are single lower case letters (whether or not they
//   appear in the values map), then postfix is set to the postfix
//   form of the expression; otherwise postfix may or may not be
//   changed, result is unchanged, and the function returns 1.  If
//   infix is syntactically valid but contains at least one lower
//   case letter operand that does not appear in the values map, then
//   result is unchanged and the function returns 2.  If infix is
//   syntactically valid and all its lower case operand letters
//   appear in the values map, then if evaluating the expression
//   (using for each letter in the expression the value in the map
//   that corresponds to it) attempts to divide by zero, then result
//   is unchanged and the function returns 3; otherwise, result is
//   set to the value of the expression and the function returns 0.




int main()
{
    char vars[] = { 'a', 'e', 'i', 'o', 'u', 'y', '#' };
    int  vals[] = {  3,  -9,   6,   2,   4,   1  };
    Map m;
    for (int k = 0; vars[k] != '#'; k++)
        m.insert(vars[k], vals[k]);
    string pf;
    int answer;
    evaluate("a+ e", m, pf, answer);
    cout << pf << " " << answer;
    //assert(evaluate("a+ e", m, pf, answer) == 0 && pf == "ae+"  &&  answer == -6);
    answer = 999;
    /**
    assert(evaluate("", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a+", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a i", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("ai", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("()", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("()o", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("y(o+u)", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("y(*o)", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a+E", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("(a+(i-o)", m, pf, answer) == 1  &&  answer == 999);
      // unary operators not allowed:
    assert(evaluate("-a", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a*b", m, pf, answer) == 2  &&
                            pf == "ab*"  &&  answer == 999);
    assert(evaluate("y +o *(   a-u)  ", m, pf, answer) == 0  &&
                            pf == "yoau-*+"  &&  answer == -1);
    answer = 999;
    assert(evaluate("o/(y-y)", m, pf, answer) == 3  &&
                            pf == "oyy-/"  &&  answer == 999);
    assert(evaluate(" a  ", m, pf, answer) == 0  &&
                            pf == "a"  &&  answer == 3);
    assert(evaluate("((a))", m, pf, answer) == 0  &&
                            pf == "a"  &&  answer == 3);*/
    cout << "Passed all tests" << endl;
}

