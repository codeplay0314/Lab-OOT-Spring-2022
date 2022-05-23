#ifndef _BOARD_H_
#define _BOARD_H_

#include <memory>
#include "canvas.h"
#include "gray_scale.h"
#include "coordinate.h"

class Board {
public:
    Board(int n, int gscale);

    int GetSize();
    std::vector<std::vector<int>>* GetCanvas();

    int GetGray();
    void SetGray(int gray);
    int GetColor();
    bool Plot(Coordinate coor);
private:
    Canvas _canvas;
    int _size;

    int _gray = 0;
    std::shared_ptr<GrayScale> _gscale;
};

#endif