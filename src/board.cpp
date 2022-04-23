#include <iostream>
#include "board.h"

shared_ptr<Board> Board::_instance;
const int Board::size = 10;

void Board::Show() {
    for (int j = size - 1; j >= 0; j--) {
        for (int i = 0; i < size; i++) {
            cout << (*_canvas.Get())[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

void Board::Plot(Coordinate coor) {
    _canvas.Set(coor, Board::GetColor());
}

int Board::GetColor() {
    return 1;
}