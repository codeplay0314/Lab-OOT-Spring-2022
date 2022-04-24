
#include "cmd_invoker.h"

CommandInvoker::CommandInvoker(shared_ptr<Board> board) : _board(board) {}

void CommandInvoker::Execute(shared_ptr<Command> command) {
    if (command->Undoable()) command->SaveState();
    command->Execute();
    if (command->Undoable()) {
        while (!_redo_stack.empty()) _redo_stack.pop();
        _undo_stack.push(command);
    }
}

void CommandInvoker::Undo() {
    if (_undo_stack.empty()) return;
    shared_ptr<Command> cmd = _undo_stack.top();
    _undo_stack.pop();
    cmd->Undo();
    _redo_stack.push(cmd);
}

void CommandInvoker::Redo() {
    if (_redo_stack.empty()) return;
    shared_ptr<Command> cmd = _redo_stack.top();
    _redo_stack.pop();
    cmd->Execute();
    _undo_stack.push(cmd);
}
