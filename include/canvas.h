#ifndef _CANVAS_H_
#define _CANVAS_H_

#include <memory>
#include <vector>
#include "coordinate.h"
using namespace std;

class Canvas {
public:
    vector<vector<int>>* Get();
    void Set(Coordinate coor, int color) {
        _canvas[coor.x()][coor.y()] = color;
    }
    
    Canvas(int n) : _canvas(n, vector<int>(n, 0)) {}
private:
    vector<vector<int>> _canvas;
};

#endif