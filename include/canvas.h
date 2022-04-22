#ifndef _CANVAS_H_
#define _CANVAS_H_

#include <vector>
#include <memory>
using namespace std;

class Canvas {
public:
    typedef vector<vector<int>> canvas;
    Canvas(int n) : _ptr(new canvas(n, vector<int>(n, 0))) {}
    shared_ptr<canvas> get();

private:
    shared_ptr<canvas> _ptr;
};

#endif