#ifndef _BOARD_H_
#define _BOARD_H_

#include <memory>
#include "canvas.h"
using namespace std;

class Board {
    static shared_ptr<Board> _instance;
    static const int size;
    
    Canvas _canvas;

public:
    Board(int n) : _canvas(n) {}
    static shared_ptr<Board> Instance() {
        if (!_instance) _instance = make_shared<Board>(size);
        return _instance;
    }

    void show();
};

#endif