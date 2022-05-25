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
    virtual std::shared_ptr<Board> GetBoard() { return _board; }
    virtual std::string GetInfo() { return _info; }
    virtual void SetExecuted(bool executed) { _executed = executed; }
    virtual void SetPreBoard(std::shared_ptr<Board> pre_board) { _pre_board = pre_board; }
    virtual void SetInfo(const std::string& info) { _info = info; }

    virtual std::shared_ptr<Command> New();
    static std::shared_ptr<Command> New(CommandType type);
    virtual std::shared_ptr<Command> Copy();
    virtual std::shared_ptr<Command> Copy(const Coordinate& offset);

    Command() {};
    Command(CommandType type) : _type(type) {};
protected:
    CommandType _type;
    std::shared_ptr<Board> _board;
    std::shared_ptr<Board> _pre_board;
    bool _executed = false;
    bool _undoable = true;
    std::string _info;
};

class ShowCommand : public Command {
public:
    virtual void Execute() override;

    ShowCommand(std::shared_ptr<Board> board);
    virtual std::shared_ptr<Command> New() override;
    static std::shared_ptr<ShowCommand> New(std::shared_ptr<Board> board);
};

class LineCommand : public Command {
public:
    virtual void Execute() override;
    virtual void Execute(Coordinate) override;

    LineCommand(std::shared_ptr<Board> board, Coordinate& begin, Coordinate& end);
    virtual std::shared_ptr<Command> New() override;
    static std::shared_ptr<LineCommand> New(std::shared_ptr<Board> board, Coordinate& begin, Coordinate& end);
private:
    Coordinate _begin, _end;
};

class TextCommand : public Command {
public:
    virtual void Execute() override;
    virtual void Execute(Coordinate) override;

    TextCommand(std::shared_ptr<Board> board, Coordinate& offset, const std::string& text);
    virtual std::shared_ptr<Command> New() override;
    static std::shared_ptr<TextCommand> New(std::shared_ptr<Board> board, Coordinate& offset, const std::string& text);
private:
    Coordinate _offset;
    std::string _text;
};

class ColorCommand : public Command {
public:
    virtual void Execute() override;

    ColorCommand(std::shared_ptr<Board> board, int color, bool undoable);
    virtual std::shared_ptr<Command> New() override;
    static std::shared_ptr<ColorCommand> New(std::shared_ptr<Board> board, int color, bool undoable);
private:
    int _gray;
    int _pre_gray;
};

class MacroCommand : public Command {
public:
    virtual void Execute() override;
    virtual void Execute(Coordinate) override;
    virtual void SetExecuted(bool executed) override;

    std::string GetName() { return _name; }

    MacroCommand(std::shared_ptr<Board> board, const std::string& name, const Coordinate& offset, std::vector<std::shared_ptr<Command>>& commands);
    static std::shared_ptr<MacroCommand> New(std::shared_ptr<Board> board, const std::string& name, const Coordinate& offset, std::vector<std::shared_ptr<Command>>& commands);
    std::shared_ptr<Command> Copy() override;
    std::shared_ptr<Command> Copy(const Coordinate& offset) override;
    void SetOffset(const Coordinate& offset);
private:
    std::vector<std::shared_ptr<Command>> _commands;
    Coordinate _offset;
    std::string _name;
};

#endif