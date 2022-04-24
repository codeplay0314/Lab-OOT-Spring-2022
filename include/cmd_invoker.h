#ifndef _CMD_INVOKER_H_
#define _CMD_INVOKER_H_

#include <stack>
#include "command.h"

class CommandInvoker {
public:
    void Execute(shared_ptr<Command> command);
    void Undo();
    void Redo();
    
    CommandInvoker(shared_ptr<Board> board);
private:
    shared_ptr<Board> _board;
    stack<shared_ptr<Command>> _undo_stack;
    stack<shared_ptr<Command>> _redo_stack;
};

#endif