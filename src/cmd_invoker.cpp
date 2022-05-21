
#include <iostream>
#include "cmd_invoker.h"

void CommandInvoker::Execute(vector<shared_ptr<Command>> cmds) {
    for (auto cmd : cmds) {
        // shared_ptr<Board> board = cmd->GetBoard();
        CommandType type = cmd->GetType();
        if (type == MACRO) {
            cout << "Execute Macro Command: " + dynamic_pointer_cast<MacroCommand>(cmd)->GetName() << endl;
            Execute(cmd);
        } else if (type == CommandType::UNDO) {
            cout << "Execute Undo Command" << endl;
            Undo();
        } else if (type == CommandType::REDO) {
            cout << "Execute Redo Command" << endl;
            Redo();
        } else if (type == CommandType::LINE) {
            cout << "Execute Line Command" << endl;
            Execute(cmd);
        } else if (type == CommandType::TEXT) {
            cout << "Execute Text Command" << endl;
            Execute(cmd);
        } else if (type == CommandType::COLOR) {
            cout << "Execute Color Command" << endl;
            Execute(cmd);
        }

        if (type == CommandType::COLOR) {
            cout << endl;
        } else {
            Execute(ShowCommand::New(_board));
        }
    }
}

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
