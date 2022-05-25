#include <iostream>
#include "cmd_invoker.h"

void CommandInvoker::Execute(std::vector<std::shared_ptr<Command>> cmds) {
    for (auto cmd : cmds) {
        CommandType type = cmd->GetType();
        if (type == MACRO) {
            std::cout << "Execute Macro Command: " + std::dynamic_pointer_cast<MacroCommand>(cmd)->GetName() << std::endl;
            Execute(cmd);
        } else if (type == CommandType::UNDO) {
            std::cout << "Execute Undo Command" << std::endl;
            Undo();
        } else if (type == CommandType::REDO) {
            std::cout << "Execute Redo Command" << std::endl;
            Redo();
        } else {
            std::cout << "Execute Command: " + cmd->GetInfo() << std::endl;
            Execute(cmd);
        }

        if (type == CommandType::COLOR) {
            std::cout << std::endl;
        } else {
            Execute(ShowCommand::New(_board));
        }
    }
}

void CommandInvoker::Execute(std::shared_ptr<Command> command) {
    if (command->Undoable()) command->SaveState();
    command->Execute();
    if (command->Undoable()) {
        while (!_redo_stack.empty()) _redo_stack.pop();
        _undo_stack.push(command);
    }
}

void CommandInvoker::Undo() {
    if (_undo_stack.empty()) return;
    std::shared_ptr<Command> cmd = _undo_stack.top();
    _undo_stack.pop();
    cmd->Undo();
    _redo_stack.push(cmd);
}

void CommandInvoker::Redo() {
    if (_redo_stack.empty()) return;
    std::shared_ptr<Command> cmd = _redo_stack.top();
    _redo_stack.pop();
    cmd->Execute();
    _undo_stack.push(cmd);
}
