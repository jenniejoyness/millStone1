#ifndef MILLSTONE_EXPRESSIONCOMMAND_H
#define MILLSTONE_EXPRESSIONCOMMAND_H

#include "Command.h"
#include "Expression.h"


class ExpressionCommand : public Expression {
private:
    Command *command;
public:
    ExpressionCommand(Command *command);

    Command *getCommand();

    double Calculate() override;
    ~ExpressionCommand();

};


#endif //MILLSTONE_EXPRESSIONCOMMAND_H
