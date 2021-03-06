#include <cctype>
#include <algorithm>
#include <bits/stdc++.h>
#include "ShuntingYard.h"
#include "Num.h"
#include "Minus.h"
#include "Plus.h"
#include "Mult.h"
#include "Div.h"



int ShuntingYard::getPriority(string C)
{
    if (C == "-" || C == "+")
        return 1;
    else if (C == "*" || C == "/")
        return 2;
    else if (C == "^")
        return 3;
    return 0;
}

/*
 * replaces the string with an expression object
 */
Expression* ShuntingYard::infixToPostfix(string str){
    stack<string> stack;
    stack.push("N");
    //splitting the string into chunks and swapping the vars for numbers
    vector<string> s = checkMinus(swapVars(splitString(str)));

    int l = s.size();
    vector<string>  output;
    for(int i = 0; i < l; i++)
    {
        // If the scanned character is an operand, add it to output string.
        if(!isOperator(s[i][0]) && s[i]!= "(" && s[i]!= ")")
            output.push_back((s[i]));

            // If the scanned character is an ‘(‘, push it to the stack.
        else if(s[i] == "(")
            stack.push("(");

            // If the scanned character is an ‘)’, pop and to output string from the stack
            // until an ‘(‘ is encountered.
        else if(s[i] == ")")
        {
            while(stack.top() != "N" && stack.top() != "(")
            {
                string c = stack.top();
                stack.pop();
                output.push_back((c));
            }
            if(stack.top() == "(")
            {
                string c = stack.top();
                stack.pop();
            }
        }
            //If an operator is scanned
        else{
            while(stack.top() != "N" && getPriority(s[i]) <= getPriority(stack.top()))
            {
                string c = stack.top();
                stack.pop();
                output.push_back((c));
            }
            stack.push(s[i]);
        }
    }
    //Pop all the remaining elements from the stack
    while(stack.top() != "N")
    {
        string c = stack.top();
        stack.pop();
        output.push_back((c));
    }
    return stringToExpression(output);
}

/*
 * creating expression objects by the operator sign
 */
Expression* ShuntingYard::stringToExpression(vector<string> postfix){
    stack<Expression*> stack;
    Expression* newExpression;
    for (auto post : postfix){
        if(!isOperator(post[0]) || (isOperator(post[0]) && post.size() != 1)){
            newExpression = new Num(stod(post));
            stack.push(newExpression);
            toBeDeleted.push_back(newExpression);
        }
        else {
            Expression* right = stack.top();
            stack.pop();
            Expression* left = stack.top();
            stack.pop();
            switch (post[0]){
                case '+':
                    newExpression = new Plus(left,right);
                    stack.push(newExpression);
                    toBeDeleted.push_back(newExpression);
                    break;
                case '-':
                    newExpression = new Minus(left,right);
                    stack.push(newExpression);
                    toBeDeleted.push_back(newExpression);
                    break;
                case '/':
                    newExpression = new Div(left,right);
                    stack.push(newExpression);
                    toBeDeleted.push_back(newExpression);
                    break;
                case '*':
                    newExpression = new Mult(left,right);
                    stack.push(newExpression);
                    toBeDeleted.push_back(newExpression);
                    break;
            }

        }
    }
    Expression* result = stack.top();
    return result;
}

bool ShuntingYard::isOperator(char s){
    if (s == '+' || s == '-' || s == '/' || s == '*'){
        return true;
    }
    return false;
}

vector<string> ShuntingYard::splitString(string str) {
    vector<string> chopped;
    int i = 0;
    string s;
    //going over the whole string
    while (i != str.length()) {
        //if is not an operator or brackets
        if(!isOperator(str[i]) && str[i]!= '(' && str[i]!= ')' && str[i]!= ' ') {
            s += str[i];
        } else {
            if (!s.empty()){
                chopped.push_back(s);
            }
            //adding operator or '(' or ')'
            if (str[i]!= ' ') {
                switch (str[i]) {
                    case 42:
                        chopped.emplace_back("*");
                        break;
                    case 43:
                        chopped.emplace_back("+");
                        break;
                    case 45:
                        chopped.emplace_back("-");
                        break;
                    case 47:
                        chopped.emplace_back("/");
                        break;
                    case 40:
                        chopped.emplace_back("(");
                        break;
                    case 41:
                        chopped.emplace_back(")");
                        break;
                }

            }
            s = "";
        }
        i++;
    }
    if (!s.empty()) {
        chopped.push_back(s);
    }
    return chopped;
}

/*
 * swaps the var in the map to the double value in the map
 */
vector<string> ShuntingYard::swapVars(vector<string> chunks) {
    for (int i = 0; i < chunks.size(); i++) {
        //is a var in the symbol table map
        if(data->isVar(chunks[i])) {
            if (data->isVarPath(chunks[i])) {
                string path = data->getPathOfVar(chunks[i]);
                chunks[i] = to_string(data->getValueByPath(path));
            } else {
                chunks[i] = to_string(data->getValueOfVar(chunks[i]));
            }
        }
    }
    return chunks;
}

/*
 * swap any unary minus operators with (0-x)
 */
vector<string> ShuntingYard::checkMinus(vector<string> str) {
    int flag = 0;
    vector<string> s;
    int bracketsNum = 1;

    for (int i = 0; i < str.size(); i++) {
        if (i == 0) {
            //check if in the first place there is a minus
            if (str[i][0] == '-') {
                s.emplace_back("(");
                s.emplace_back("0");
                //if it's because negative number split it into two cells
                if (str[i].size() > 1) {
                    s.emplace_back("-");
                    s.emplace_back(str[i].substr(1, str[i].size()));
                    //if no- insert as is
                } else {
                    s.emplace_back(str[i]);
                }
                flag = 1;
            } else {
                s.emplace_back(str[i]);
            }
            continue;
        }
        int j = 0;
        //if was minus and now there is a number - insert it and (
        if (flag && !isOperator(str[i][0])) {
            s.emplace_back(str[i]);
            while (j < bracketsNum) {
                s.emplace_back(")");
                j++;
            }
            flag = 0;
            continue;
            //if its another operator
        } else if (flag && str[i][0] != '-') {
            while (j < bracketsNum) {
                s.emplace_back(")");
                j++;
            }
            flag = 0;
            //if its minus again
        } else if (flag) {
            bracketsNum++;
        }
        //if its minus and before it was operator or (
        if ((isOperator(str[i - 1][0]) || str[i - 1] == "(") && str[i][0] == '-') {
            s.emplace_back( "(");
            s.emplace_back("0");
            if (str[i].size() > 1) {
                s.emplace_back("-");
                s.emplace_back(str[i].substr(1, str[i].size()));
            } else {
                s.emplace_back(str[i]);
            }
            flag = 1;
        } else {
            s.emplace_back(str[i]);
        }
    }
    int j = 0;
    if (flag) {
        while (j < bracketsNum) {
            s.emplace_back(")");
            j++;
        }
        s.emplace_back(")");
    }
    return s;
}
ShuntingYard::~ShuntingYard() {
    for(auto expression: toBeDeleted){
        delete(expression);
    }
}
