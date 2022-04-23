#include "command.h"

shared_ptr<CommandInvoker> CommandInvoker::_instance;

LineCommand::LineCommand (shared_ptr<Board> board, vector<int> args) :
    _board(board), begin(args[0], args[1]), end(args[2], args[3]) {}

void LineCommand::Execute() {
    // Bresenham's line algorithm
    int dx = end.x() - begin.x();
    int dy = end.y() - begin.y();
    double k = (double)dy / dx;

    for (int x = begin.x(), y = begin.y(), e = -x; x <= end.x(); x++) {
        _board->Plot(Coordinate(x, y));
        e += 2 * dy;
        if (e > 0) e -= 2 * dx, y++;
    }
}