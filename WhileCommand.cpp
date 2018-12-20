//
// Created by jennie on 12/20/18.
//

#include <cstring>
#include "WhileCommand.h"
#include "ShuntingYard.h"
#include "ConditionOperators.h"


void WhileCommand::doCommand() {

    //ConditionOperator;
    while(stuff(condition)){
        for (int i = 0; i < commands.size(); ++i) {
            //if the command is not a while command send to parser to execute
            if (strstr(commands[i][0].c_str(), "while") == NULL || strstr(commands[i][0].c_str(), "if") == NULL) {
                if (commands[i][0] != "{" || commands[i][0] != "}") {
                    reader.parser(commands[i]);
                }
                //otherwise send to condition parser
            } else {
                reader.conditionParser(commands[i][0]);
            }
        }
    }
}


void WhileCommand::setParameters(vector<string> params, Data *data) {
    this->condition = params;
    this->data = data;
}
