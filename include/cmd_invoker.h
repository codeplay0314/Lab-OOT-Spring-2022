#ifndef _CMD_INVOKER_H_
#define _CMD_INVOKER_H_

#include "command.h"

class CommandInvoker {
    shared_ptr<Board> _board;
public:
    CommandInvoker(shared_ptr<Board> board);

    void Execute(Command& command) {
        command.Execute(_board);
    }
};

#endif