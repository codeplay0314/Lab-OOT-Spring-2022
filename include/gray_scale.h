#ifndef _GRAYSCALE_H_
#define _GRAYSCALE_H_

#include <memory>
using namespace std;

class GrayScale {
public:
    virtual int GetColor(int) = 0;
};

class BW2Scale : public GrayScale {
    static shared_ptr<GrayScale> _instance;
public:
    static shared_ptr<GrayScale> Instance();

    virtual int GetColor(int gray);
};

class BW256Scale : public GrayScale {
    static shared_ptr<GrayScale> _instance;
public:
    static shared_ptr<GrayScale> Instance();

    virtual int GetColor(int gray);
};

#endif