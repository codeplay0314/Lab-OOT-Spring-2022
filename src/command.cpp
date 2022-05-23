#include <iostream>
#include "command.h"
#include "char_lib.h"
#include "cmd_invoker.h"

//Command
void Command::Execute(Coordinate) {
    Execute();
}

void Command::Undo() {
    if (!_undoable || !_pre_board) exit(0);
    SetExecuted(false);
    *_board = *_pre_board;
}

bool Command::Undoable() {
    return _undoable;
}

void Command::SaveState() {
    if (_undoable) SetPreBoard(std::make_shared<Board>(*_board));
}

std::shared_ptr<Command> Command::New(CommandType type) {
    return std::make_shared<Command>(type);
}

std::shared_ptr<Command> Command::New() {
    return std::make_shared<Command>();
}

std::shared_ptr<Command> Command::Copy() {
    return Copy(Coordinate(0, 0));
}

std::shared_ptr<Command> Command::Copy(const Coordinate& offset) {
    std::shared_ptr<Command> new_cmd = this->New();
    _executed = false;
    _pre_board = 0;
    return new_cmd;
}

// ShowCommand
ShowCommand::ShowCommand(std::shared_ptr<Board> board) {
    _type = CommandType::SHOW;
    _undoable = false;
    _board = board;
}

std::shared_ptr<Command> ShowCommand::New() {
    return New(_board);
}

std::shared_ptr<ShowCommand> ShowCommand::New(std::shared_ptr<Board> board) {
    return std::make_shared<ShowCommand>(board);
}

void ShowCommand::Execute() {
    if (_executed) exit(0);
    _executed = true;

    int size = _board->GetSize();
    std::vector<std::vector<int>>* canvas = _board->GetCanvas();
    for (int j = size - 1; j >= 0; j--) {
        for (int i = 0; i < size; i++) {
            if (i) std::cout << " ";
            std::cout << (*canvas)[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// LineCommand
LineCommand::LineCommand(std::shared_ptr<Board> board, Coordinate& begin, Coordinate& end) : _begin(begin), _end(end) {
    _type = CommandType::LINE;
    _board = board;
}

std::shared_ptr<Command> LineCommand::New() {
    return New(_board, _begin, _end);
}

std::shared_ptr<LineCommand> LineCommand::New(std::shared_ptr<Board> board, Coordinate& begin, Coordinate& end) {
    return std::make_shared<LineCommand>(board, begin, end);
}

void LineCommand::Execute() {
    Execute(Coordinate(0, 0));
}

void LineCommand::Execute(Coordinate offset) {
    if (_executed) exit(0);
    _executed = true;

    // Bresenham's line algorithm
    int dx = _end.x() - _begin.x();
    int dy = _end.y() - _begin.y();
    if (abs(dx) >= abs(dy)) {
        if (dy < 0) {
            std::swap(_begin, _end);
            dx = -dx;
            dy = -dy;
        }
        for (int x = _begin.x(), y = _begin.y(), e = -x, aug = _begin.x() < _end.x() ? 1 : -1; ; x += aug) {
            _board->Plot(offset + Coordinate(x, y));
            e += 2 * dy;
            if (e > 0) e -= abs(2 * dx), y++;
            if (x == _end.x()) break;
        }
    } else {
        if (dx < 0) {
            std::swap(_begin, _end);
            dx = -dx;
            dy = -dy;
        }
        for (int x = _begin.x(), y = _begin.y(), e = -y, aug = _begin.y() < _end.y() ? 1 : -1; ; y += aug) {
            _board->Plot(offset + Coordinate(x, y));
            e += 2 * dx;
            if (e > 0) e -= abs(2 * dy), x++;
            if (y == _end.y()) break;
        }
    }
}

// TextCommand
TextCommand::TextCommand(std::shared_ptr<Board> board, Coordinate& offset, const std::string& text) : _offset(offset), _text(text) {
    _type = CommandType::TEXT;
    _board = board;
}

std::shared_ptr<Command> TextCommand::New() {
    return New(_board, _offset, _text);
}

std::shared_ptr<TextCommand> TextCommand::New(std::shared_ptr<Board> board, Coordinate& offset, const std::string& text) {
    return std::make_shared<TextCommand>(board, offset, text);
}

void TextCommand::Execute() {
    Execute(Coordinate(0, 0));
}

void TextCommand::Execute(Coordinate offset) {
    if (_executed) exit(0);
    _executed = true;

    Coordinate cur = offset + Coordinate(_offset.x() + 1, _offset.y());;
    for (auto c : _text) {
        std::vector<int> mat = GetCharShape(c);
        int n = mat.size();
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (mat[i]&(1<<j))
                    _board->Plot(Coordinate(cur.x() + n - j - 1, cur.y() + n - i - 1));
        cur = Coordinate(cur.x() + n + 1, cur.y());
    }
}

// ColorCommand
ColorCommand::ColorCommand(std::shared_ptr<Board> board, int gray, bool undoable) : _gray(gray) {
    _type = CommandType::COLOR;
    _board = board;
    _undoable = undoable;
}

std::shared_ptr<Command> ColorCommand::New() {
    return New(_board, _gray, _undoable);
}

std::shared_ptr<ColorCommand> ColorCommand::New(std::shared_ptr<Board> board, int gray, bool undoable) {
    return std::make_shared<ColorCommand>(board, gray, undoable);
}

void ColorCommand::Execute() {
    if (_executed) exit(0);
    _executed = true;

    _board->SetGray(_gray);
}

// MacroCommand
MacroCommand::MacroCommand(std::shared_ptr<Board> board, const std::string& name, const Coordinate& offset, std::vector<std::shared_ptr<Command>>& commands) :
    _offset(offset), _commands(commands) {
    _type = CommandType::MACRO;
    _board = board;
    _name = name;
}

std::shared_ptr<MacroCommand> MacroCommand::New(std::shared_ptr<Board> board, const std::string& name, const Coordinate& offset, std::vector<std::shared_ptr<Command>>& commands) {
    return std::make_shared<MacroCommand>(board, name, offset, commands);
}

void MacroCommand::Execute() {
    Execute(Coordinate(0, 0));
}

void MacroCommand::Execute(Coordinate offset) {
    if (_executed) exit(0);
    _executed = true;
    
    int gray = _board->GetGray();
    for (auto command : _commands) {
        command->Execute(_offset + offset);
    }
    ColorCommand::New(_board, gray, false)->Execute();
}

void MacroCommand::SetExecuted(bool executed) {
    _executed = executed;
    for (auto command : _commands) command->SetExecuted(executed);
}

std::shared_ptr<Command> MacroCommand::Copy() {
    return Copy(_offset);
}

std::shared_ptr<Command> MacroCommand::Copy(const Coordinate& offset) {
    std::vector<std::shared_ptr<Command>> new_cmds;
    for (auto command : _commands) new_cmds.push_back(command->Copy());
    return std::make_shared<MacroCommand>(_board, _name, offset, new_cmds);
}

void MacroCommand::SetOffset(const Coordinate& offset) {
    _offset = offset;
}