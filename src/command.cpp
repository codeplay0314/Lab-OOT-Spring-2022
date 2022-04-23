#include "command.h"
#include "char_lib.h"
#include "cmd_invoker.h"
#include <iostream>

//Command
void Command::Execute(shared_ptr<Board> board, Coordinate) {
    Execute(board);
}

// ShowCommand
void ShowCommand::Execute(shared_ptr<Board> board) {
    int size = board->GetSize();
    Canvas* canvas = board->GetCanvas();
    for (int j = size - 1; j >= 0; j--) {
        for (int i = 0; i < size; i++) {
            cout << (*canvas->Get())[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

// LineCommand
LineCommand::LineCommand(Coordinate& begin, Coordinate& end) : _begin(begin), _end(end) {}

void LineCommand::Execute(shared_ptr<Board> board) {
    Execute(board, Coordinate(0, 0));
}

void LineCommand::Execute(shared_ptr<Board> board, Coordinate offset) {
    // Bresenham's line algorithm
    offset = offset + _begin;
    int dx = _end.x() - _begin.x();
    int dy = _end.y() - _begin.y();
    double k = (double)dy / dx;

    for (int x = _begin.x(), y = _begin.y(), e = -x; x <= _end.x(); x++) {
        board->Plot(offset + Coordinate(x, y));
        e += 2 * dy;
        if (e > 0) e -= 2 * dx, y++;
    }
}

// TextCommand
TextCommand::TextCommand(Coordinate& offset, string& text) : _offset(offset), _text(text) {}

void TextCommand::Execute(shared_ptr<Board> board) {
    Execute(board, Coordinate(0, 0));
}

void TextCommand::Execute(shared_ptr<Board> board, Coordinate offset) {
    Coordinate cur = offset + Coordinate(_offset.x() + 1, _offset.y());;
    for (auto c : _text) {
        vector<int> mat = GetCharShape(c);
        int n = mat.size();
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (mat[i]&(1<<j))
                    board->Plot(Coordinate(cur.x() + n - j - 1, cur.y() + n - i - 1));
        cur = Coordinate(cur.x(), cur.y() + n + 1);
    }
}

// ColorCommand
ColorCommand::ColorCommand(int gray) : _gray(gray) {}

void ColorCommand::Execute(shared_ptr<Board> board) {
    board->SetGray(_gray);
}

// MacroCommand
MacroCommand::MacroCommand(string& name, Coordinate& offset, vector<shared_ptr<Command>>& commands) :
    _name(name), _offset(offset), _commands(commands) {}

void MacroCommand::Execute(shared_ptr<Board> board) {
    Execute(board, Coordinate(0, 0));
}

void MacroCommand::Execute(shared_ptr<Board> board, Coordinate offset) {
    for (auto command : _commands) {
        command->Execute(board, _offset + offset);
    }
}