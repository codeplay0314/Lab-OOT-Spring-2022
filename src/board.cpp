#include <iostream>
#include "board.h"

shared_ptr<Board> Board::_instance;

Board::Board(int n, int gscale) : _canvas(n), _size(n) {
    if (gscale == 2) _gscale = BW2Scale::Instance();
    else if (gscale == 256) _gscale = BW256Scale::Instance();
}
shared_ptr<Board> Board::Instance(int n, int gscale) {
    if (!_instance) _instance = make_shared<Board>(n, gscale);
    return _instance;
}
shared_ptr<Board> Board::Instance(int gscale) {
    if (!_instance) _instance = make_shared<Board>(50, gscale);
    return _instance;
}
shared_ptr<Board> Board::Instance() {
    if (!_instance) exit(0);
    return _instance;
}

void Board::Show() {
    for (int j = _size - 1; j >= 0; j--) {
        for (int i = 0; i < _size; i++) {
            cout << (*_canvas.Get())[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

void Board::SetGray(int gray) {
    _gray = gray;
}

int Board::GetColor() {
    return _gscale->GetColor(_gray);
}

void Board::Plot(Coordinate coor) {
    if (coor.x() < 0 || coor.x() >= _size || coor.y() < 0 || coor.y() >= _size) return;
    _canvas.Set(coor, Board::GetColor());
}