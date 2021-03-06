#include <unistd.h>
#include "SleepCommand.h"
#include "ShuntingYard.h"

void SleepCommand::setParameters(vector<string> params, Data *data) {
    ShuntingYard shuntingYard(data);
    seconds = (int) shuntingYard.infixToPostfix(params[0])->Calculate();
}

void SleepCommand::doCommand() {
    usleep(seconds);
}