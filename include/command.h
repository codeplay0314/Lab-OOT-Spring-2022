#ifndef _COMMAND_H_
#define _COMMAND_H_

#include "board.h"
#include "coordinate.h"

enum CommandType {
    MACRO,
    UNDO,
    REDO,
    SHOW,
    LINE,
    TEXT,
    COLOR
};

class Command {
public:
    virtual void Execute() {};
    virtual void Execute(Coordinate);
    virtual void Undo();
    virtual bool Undoable() final;
    virtual void SaveState();

    virtual CommandType GetType() { return _type; }
    virtual shared_ptr<Board> GetBoard() { return _board; }
    virtual void SetExecuted(bool executed) { _executed = executed; }
    virtual void SetPreBoard(shared_ptr<Board> pre_board) { _pre_board = pre_board; }

    virtual shared_ptr<Command> New();
    static shared_ptr<Command> New(CommandType type);
    virtual shared_ptr<Command> Copy();
    virtual shared_ptr<Command> Copy(const Coordinate& offset);

    Command() {};
    Command(CommandType type) : _type(type) {};
protected:
    CommandType _type;
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

    TextCommand(shared_ptr<Board> board, Coordinate& offset, const string& text);
    virtual shared_ptr<Command> New() override;
    static shared_ptr<TextCommand> New(shared_ptr<Board> board, Coordinate& offset, const string& text);
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

    MacroCommand(shared_ptr<Board> board, const Coordinate& offset, vector<shared_ptr<Command>>& commands);
    static shared_ptr<MacroCommand> New(shared_ptr<Board> board, const Coordinate& offset, vector<shared_ptr<Command>>& commands);
    shared_ptr<Command> Copy() override;
    shared_ptr<Command> Copy(const Coordinate& offset) override;
    void SetOffset(const Coordinate& offset);
private:
    vector<shared_ptr<Command>> _commands;
    Coordinate _offset;
};

#endif