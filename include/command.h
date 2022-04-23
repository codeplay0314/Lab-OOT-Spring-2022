#ifndef _COMMAND_H_
#define _COMMAND_H_

#include "board.h"
#include "coordinate.h"

class Command {
public:
    virtual void Execute() = 0;
};

class CommandInvoker {
    static shared_ptr<CommandInvoker> _instance;

public:
    static shared_ptr<CommandInvoker> Instance();

    void Execute(Command& command) {
        command.Execute();
    }
};

class LineCommand : public Command {
public:
    LineCommand(shared_ptr<Board> board, Coordinate begin, Coordinate end);

    virtual void Execute();
private:
    shared_ptr<Board> _board;
    Coordinate _begin, _end;
};

class TextCommand : public Command {
public:
    TextCommand(shared_ptr<Board> board, Coordinate begin, string text);

    virtual void Execute();
private:
    shared_ptr<Board> _board;
    Coordinate _begin;
    string _text;
};

class ColorCommand : public Command {
public:
    ColorCommand(shared_ptr<Board> board, int color);

    virtual void Execute();
private:
    shared_ptr<Board> _board;
    int _gray;
};

#endif