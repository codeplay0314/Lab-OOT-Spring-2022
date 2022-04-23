#ifndef _COORDINATE_H_
#define _COORDINATE_H_

class Coordinate {
    int _x, _y;
public:
    Coordinate(int x, int y) : _x(x), _y(y) {}
    int x() { return _x; }
    int y() { return _y; }

    Coordinate operator + (Coordinate C) const {
        Coordinate res(_x + C.x(), _y + C.y());
        return res;
    }
};

#endif