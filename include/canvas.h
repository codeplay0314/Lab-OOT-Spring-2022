#ifndef _CANVAS_H_
#define _CANVAS_H_

#include <memory>
#include <vector>
#include "coordinate.h"
using namespace std;

class Canvas {
public:
    typedef vector<vector<int>> canvas;
    Canvas(int n) : _ptr(new canvas(n, vector<int>(n, 0))) {}
    shared_ptr<canvas> Get();

    void Set(Coordinate coor, int color) {
        (*_ptr)[coor.x()][coor.y()] = color;
    }
private:
    shared_ptr<canvas> _ptr;
};

#endif