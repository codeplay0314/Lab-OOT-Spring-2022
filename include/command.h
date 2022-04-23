#ifndef _COMMAND_H_
#define _COMMAND_H_

#include "board.h"
#include "coordinate.h"

class Command {
public:
    virtual void Execute(shared_ptr<Board> board) = 0;
    virtual void Execute(shared_ptr<Board> board, Coordinate);
};

class ShowCommand : public Command {
public:
    virtual void Execute(shared_ptr<Board> board) override;
};

class LineCommand : public Command {
public:
    LineCommand(Coordinate& begin, Coordinate& end);

    virtual void Execute(shared_ptr<Board> board) override;
    virtual void Execute(shared_ptr<Board> board, Coordinate) override;
private:
    Coordinate _begin, _end;
};

class TextCommand : public Command {
public:
    TextCommand(Coordinate& offset, string& text);

    virtual void Execute(shared_ptr<Board> board) override;
    virtual void Execute(shared_ptr<Board> board, Coordinate) override;
private:
    Coordinate _offset;
    string _text;
};

class ColorCommand : public Command {
public:
    ColorCommand(int color);

    virtual void Execute(shared_ptr<Board> board) override;
private:
    int _gray;
};

class MacroCommand : public Command {
public:
    string Name() { return _name; }

    virtual void Execute(shared_ptr<Board> board) override;
    virtual void Execute(shared_ptr<Board> board, Coordinate) override;
    MacroCommand(string& name, Coordinate& offset, vector<shared_ptr<Command>>& commands);
private:
    const string _name;

    vector<shared_ptr<Command>> _commands;
    Coordinate _offset;
};

#endif