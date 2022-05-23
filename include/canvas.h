#ifndef _CANVAS_H_
#define _CANVAS_H_

#include <memory>
#include <vector>
#include "coordinate.h"

class Canvas {
public:
    std::vector<std::vector<int>>* Get();
    void Set(Coordinate coor, int color) {
        _canvas[coor.x()][coor.y()] = color;
    }
    
    Canvas(int n) : _canvas(n, std::vector<int>(n, 0)) {}
private:
    std::vector<std::vector<int>> _canvas;
};

#endif