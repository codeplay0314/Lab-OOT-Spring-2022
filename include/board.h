#ifndef _BOARD_H_
#define _BOARD_H_

#include <memory>
#include "canvas.h"
#include "coordinate.h"
using namespace std;

class Board {
    static shared_ptr<Board> _instance;
    static const int _size;
    
    Canvas _canvas;
public:
    Board(int n) : _canvas(n) {}
    static shared_ptr<Board> Instance() {
        if (!_instance) _instance = make_shared<Board>(_size);
        return _instance;
    }

    void Plot(Coordinate coor);
    int GetColor();

    void Show();
};

#endif