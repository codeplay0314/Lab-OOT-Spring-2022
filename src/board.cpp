#include <iostream>
#include "board.h"

shared_ptr<Board> Board::_instance;
const int Board::_size = 20;

void Board::Show() {
    for (int j = _size - 1; j >= 0; j--) {
        for (int i = 0; i < _size; i++) {
            cout << (*_canvas.Get())[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

void Board::Plot(Coordinate coor) {
    if (coor.x() < 0 || coor.x() >= _size || coor.y() < 0 || coor.y() >= _size) return;
    _canvas.Set(coor, Board::GetColor());
}

int Board::GetColor() {
    return 1;
}