#ifndef MILLSTONE_EQUALCOMMAND_H
#define MILLSTONE_EQUALCOMMAND_H


#include "Data.h"
#include "Command.h"

class EqualCommand:public Command {
    Data* data;
    string varTarget;
    double value;

public:
    void sendMessage(string str);
    void doCommand() override;
    void setParameters(vector<string> params, Data *data) override;

};


#endif //MILLSTONE_EQUALCOMMAND_H
