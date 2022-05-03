#ifndef _COMMAND_H_
#define _COMMAND_H_

#include "board.h"
#include "coordinate.h"

class Command {
public:
    virtual void Execute() {};
    virtual void Execute(Coordinate);
    virtual void Undo();
    virtual bool Undoable() final;
    virtual void SaveState();

    virtual void SetExecuted(bool executed) { _executed = executed; }
    virtual void SetPreBoard(shared_ptr<Board> pre_board) { _pre_board = pre_board; }

    virtual shared_ptr<Command> New();
    virtual shared_ptr<Command> Copy();
protected:
    shared_ptr<Board> _board;
    shared_ptr<Board> _pre_board;
    bool _executed = false;
    bool _undoable = true;
};

class ShowCommand : public Command {
public:
    virtual void Execute() override;

    ShowCommand(shared_ptr<Board> board);
    virtual shared_ptr<Command> New() override;
    static shared_ptr<ShowCommand> New(shared_ptr<Board> board);
};

class LineCommand : public Command {
public:
    virtual void Execute() override;
    virtual void Execute(Coordinate) override;

    LineCommand(shared_ptr<Board> board, Coordinate& begin, Coordinate& end);
    virtual shared_ptr<Command> New() override;
    static shared_ptr<LineCommand> New(shared_ptr<Board> board, Coordinate& begin, Coordinate& end);
private:
    Coordinate _begin, _end;
};

class TextCommand : public Command {
public:
    virtual void Execute() override;
    virtual void Execute(Coordinate) override;

    TextCommand(shared_ptr<Board> board, Coordinate& offset, string& text);
    virtual shared_ptr<Command> New() override;
    static shared_ptr<TextCommand> New(shared_ptr<Board> board, Coordinate& offset, string& text);
private:
    Coordinate _offset;
    string _text;
};

class ColorCommand : public Command {
public:
    virtual void Execute() override;

    ColorCommand(shared_ptr<Board> board, int color, bool undoable);
    virtual shared_ptr<Command> New() override;
    static shared_ptr<ColorCommand> New(shared_ptr<Board> board, int color, bool undoable);
private:
    int _gray;
    int _pre_gray;
};

class MacroCommand : public Command {
public:
    virtual void Execute() override;
    virtual void Execute(Coordinate) override;
    virtual void SetExecuted(bool executed) override;

    MacroCommand(shared_ptr<Board> board, Coordinate& offset, vector<shared_ptr<Command>>& commands);
    static shared_ptr<MacroCommand> New(shared_ptr<Board> board, Coordinate& offset, vector<shared_ptr<Command>>& commands);
    shared_ptr<Command> Copy() override;
private:
    vector<shared_ptr<Command>> _commands;
    Coordinate _offset;
};

#endif