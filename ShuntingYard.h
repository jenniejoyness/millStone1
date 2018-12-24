
#ifndef MILLSTONE_SHUNTINGYARD_H
#define MILLSTONE_SHUNTINGYARD_H
using namespace std;

#include <iostream>
#include "Expression.h"
#include "Data.h"
#include <vector>

class ShuntingYard {
    Data* data;
public:
    ShuntingYard(Data* data){
        this->data = data;
    }
    vector<string> splitString(string str);
    int getPriority(string C);
    Expression*  infixToPostfix(string str);
    Expression* stringToExpression(vector<string>  postfix);
    bool isOperator(char s);
    vector<string> swapVars(vector<string> withVars);
    string checkMinus(string str);
};

#endif //MILLSTONE_SHUNTINGYARD_H
