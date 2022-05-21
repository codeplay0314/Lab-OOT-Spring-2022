#ifndef _CMD_INVOKER_H_
#define _CMD_INVOKER_H_

#include <stack>
#include "command.h"

class CommandInvoker {
public:
    void Execute(vector<shared_ptr<Command>> command);
    void Execute(shared_ptr<Command> command);
    void Undo();
    void Redo();
    
    CommandInvoker() {};
private:
    stack<shared_ptr<Command>> _undo_stack;
    stack<shared_ptr<Command>> _redo_stack;
};

#endif