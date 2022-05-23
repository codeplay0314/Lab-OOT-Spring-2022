#include "board.h"

Board::Board(int n, int gscale) : _canvas(n), _size(n) {
    if (gscale == 2) _gscale = BW2Scale::Instance();
    else if (gscale == 256) _gscale = BW256Scale::Instance();
}

int Board::GetSize() {
    return _size;
}

std::vector<std::vector<int>>* Board::GetCanvas() {
    return _canvas.Get();
}

int Board::GetGray() {
    return _gray;
}

void Board::SetGray(int gray) {
    _gray = gray;
}

int Board::GetColor() {
    return _gscale->GetColor(_gray);
}

bool Board::Plot(Coordinate coor) {
    if (coor.x() < 0 || coor.x() >= _size || coor.y() < 0 || coor.y() >= _size) return false;
    _canvas.Set(coor, Board::GetColor());
    return true;
}