#include <iostream>
#include "board.h"

shared_ptr<Board> Board::_instance;
const int Board::size = 10;

void Board::show() {
    shared_ptr<Canvas::canvas> canvas = _canvas.get();
    for (auto row : *canvas) {
        for (auto num : row) {
            cout << num;
        }
        cout << endl;
    }
}