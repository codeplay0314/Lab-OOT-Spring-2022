#include "command.h"
#include "char_lib.h"

// CommandInvoker
shared_ptr<CommandInvoker> CommandInvoker::_instance;

shared_ptr<CommandInvoker> CommandInvoker::Instance() {
    if (!_instance) _instance = make_shared<CommandInvoker>();
    return _instance;
}

// LineCommand
LineCommand::LineCommand(shared_ptr<Board> board, Coordinate begin, Coordinate end) :
    _board(board), _begin(begin), _end(end) {}

void LineCommand::Execute() {
    // Bresenham's line algorithm
    int dx = _end.x() - _begin.x();
    int dy = _end.y() - _begin.y();
    double k = (double)dy / dx;

    for (int x = _begin.x(), y = _begin.y(), e = -x; x <= _end.x(); x++) {
        _board->Plot(Coordinate(x, y));
        e += 2 * dy;
        if (e > 0) e -= 2 * dx, y++;
    }
}

// TextCommand
TextCommand::TextCommand(shared_ptr<Board> board, Coordinate begin, string text) :
    _board(board), _begin(begin), _text(text) {}

void TextCommand::Execute() {
    Coordinate cur = Coordinate(_begin.x() + 1, _begin.y());;
    for (auto c : _text) {
        vector<int> mat = GetCharShape(c);
        int n = mat.size();
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (mat[i]&(1<<j)) {
                    Coordinate coor(cur.x() + n - j - 1, cur.y() + n - i - 1);
                    _board->Plot(coor);
                }
        cur = Coordinate(cur.x(), cur.y() + n + 1);
    }
}

// ColorCommand
ColorCommand::ColorCommand(shared_ptr<Board> board, int gray) :
    _board(board), _gray(gray) {}

void ColorCommand::Execute() {
    _board->SetGray(_gray);
}