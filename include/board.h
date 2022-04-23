#ifndef _BOARD_H_
#define _BOARD_H_

#include <memory>
#include "canvas.h"
#include "gray_scale.h"
#include "coordinate.h"
using namespace std;

class Board {
    static shared_ptr<Board> _instance;
    
    Canvas _canvas;
    const int _size;

    int _gray = 0;
    shared_ptr<GrayScale> _gscale;
public:
    Board(int n, int gscale);

    static shared_ptr<Board> Instance(int n, int gscale);
    static shared_ptr<Board> Instance(int gscale);
    static shared_ptr<Board> Instance();

    void SetGray(int gray);
    int GetColor();
    void Plot(Coordinate coor);

    void Show();
};

#endif