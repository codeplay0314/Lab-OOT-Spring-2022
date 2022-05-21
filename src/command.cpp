#include "command.h"
#include "char_lib.h"
#include "cmd_invoker.h"
#include <iostream>

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
    if (_undoable) SetPreBoard(make_shared<Board>(*_board));
}

shared_ptr<Command> Command::New(CommandType type) {
    return make_shared<Command>(type);
}

shared_ptr<Command> Command::New() {
    return make_shared<Command>();
}

shared_ptr<Command> Command::Copy() {
    return Copy(Coordinate(0, 0));
}

shared_ptr<Command> Command::Copy(const Coordinate& offset) {
    shared_ptr<Command> new_cmd = this->New();
    _executed = false;
    _pre_board = 0;
    return new_cmd;
}

// ShowCommand
ShowCommand::ShowCommand(shared_ptr<Board> board) {
    _type = CommandType::SHOW;
    _undoable = false;
    _board = board;
}

shared_ptr<Command> ShowCommand::New() {
    return New(_board);
}

shared_ptr<ShowCommand> ShowCommand::New(shared_ptr<Board> board) {
    return make_shared<ShowCommand>(board);
}

void ShowCommand::Execute() {
    if (_executed) exit(0);
    _executed = true;

    int size = _board->GetSize();
    vector<vector<int>>* canvas = _board->GetCanvas();
    for (int j = size - 1; j >= 0; j--) {
        for (int i = 0; i < size; i++) {
            cout << (*canvas)[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

// LineCommand
LineCommand::LineCommand(shared_ptr<Board> board, Coordinate& begin, Coordinate& end) : _begin(begin), _end(end) {
    _type = CommandType::LINE;
    _board = board;
}

shared_ptr<Command> LineCommand::New() {
    return New(_board, _begin, _end);
}

shared_ptr<LineCommand> LineCommand::New(shared_ptr<Board> board, Coordinate& begin, Coordinate& end) {
    return make_shared<LineCommand>(board, begin, end);
}

void LineCommand::Execute() {
    Execute(Coordinate(0, 0));
}

void LineCommand::Execute(Coordinate offset) {
    if (_executed) exit(0);
    _executed = true;

    // Bresenham's line algorithm
    offset = offset + _begin;
    int dx = _end.x() - _begin.x();
    int dy = _end.y() - _begin.y();
    double k = (double)dy / dx;

    for (int x = _begin.x(), y = _begin.y(), e = -x; x <= _end.x(); x++) {
        _board->Plot(offset + Coordinate(x, y));
        e += 2 * dy;
        if (e > 0) e -= 2 * dx, y++;
    }
}

// TextCommand
TextCommand::TextCommand(shared_ptr<Board> board, Coordinate& offset, const string& text) : _offset(offset), _text(text) {
    _type = CommandType::TEXT;
    _board = board;
}

shared_ptr<Command> TextCommand::New() {
    return New(_board, _offset, _text);
}

shared_ptr<TextCommand> TextCommand::New(shared_ptr<Board> board, Coordinate& offset, const string& text) {
    return make_shared<TextCommand>(board, offset, text);
}

void TextCommand::Execute() {
    Execute(Coordinate(0, 0));
}

void TextCommand::Execute(Coordinate offset) {
    if (_executed) exit(0);
    _executed = true;

    Coordinate cur = offset + Coordinate(_offset.x() + 1, _offset.y());;
    for (auto c : _text) {
        vector<int> mat = GetCharShape(c);
        int n = mat.size();
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (mat[i]&(1<<j))
                    _board->Plot(Coordinate(cur.x() + n - j - 1, cur.y() + n - i - 1));
        cur = Coordinate(cur.x(), cur.y() + n + 1);
    }
}

// ColorCommand
ColorCommand::ColorCommand(shared_ptr<Board> board, int gray, bool undoable) : _gray(gray) {
    _type = CommandType::COLOR;
    _board = board;
    _undoable = undoable;
}

shared_ptr<Command> ColorCommand::New() {
    return New(_board, _gray, _undoable);
}

shared_ptr<ColorCommand> ColorCommand::New(shared_ptr<Board> board, int gray, bool undoable) {
    return make_shared<ColorCommand>(board, gray, undoable);
}

void ColorCommand::Execute() {
    if (_executed) exit(0);
    _executed = true;    

    _board->SetGray(_gray);
}

// MacroCommand
MacroCommand::MacroCommand(shared_ptr<Board> board, const Coordinate& offset, vector<shared_ptr<Command>>& commands) :
    _offset(offset), _commands(commands) {
    _type = CommandType::MACRO;
    _board = board;
}

shared_ptr<MacroCommand> MacroCommand::New(shared_ptr<Board> board, const Coordinate& offset, vector<shared_ptr<Command>>& commands) {
    return make_shared<MacroCommand>(board, offset, commands);
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

shared_ptr<Command> MacroCommand::Copy() {
    return Copy(_offset);
}

shared_ptr<Command> MacroCommand::Copy(const Coordinate& offset) {
    vector<shared_ptr<Command>> new_cmds;
    for (auto command : _commands) new_cmds.push_back(command->Copy());
    return make_shared<MacroCommand>(_board, offset, new_cmds);
}

void MacroCommand::SetOffset(const Coordinate& offset) {
    _offset = offset;
}