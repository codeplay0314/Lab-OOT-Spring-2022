#ifndef _COORDINATE_H_
#define _COORDINATE_H_

class Coordinate {
public:
    int x() { return _x; }
    int y() { return _y; }

    Coordinate(int x, int y) : _x(x), _y(y) {}
    Coordinate operator + (Coordinate C) const {
        Coordinate res(_x + C.x(), _y + C.y());
        return res;
    }
private:
    int _x, _y;
};

#endif