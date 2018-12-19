
#ifndef MILLSTONE_SHUNTINGYARD_H
#define MILLSTONE_SHUNTINGYARD_H
using namespace std;

#include <iostream>
#include "Expression.h"
#include <vector>

class ShuntingYard {
public:
    vector<string> splitString(string str);
    int getPriority(string C);
    Expression*  infixToPostfix(string str);
    Expression* stringToExpression(vector<string>  postfix);
    bool isOperator(char s);
};

#endif //MILLSTONE_SHUNTINGYARD_H
