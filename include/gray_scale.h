#ifndef _GRAYSCALE_H_
#define _GRAYSCALE_H_

#include <memory>

class GrayScale {
public:
    virtual int GetColor(int) = 0;
};

class BW2Scale : public GrayScale {
public:
    virtual int GetColor(int gray);
    
    static std::shared_ptr<GrayScale> Instance();
private:
    static std::shared_ptr<GrayScale> _instance;
};

class BW256Scale : public GrayScale {
public:
    virtual int GetColor(int gray);
    
    static std::shared_ptr<GrayScale> Instance();
private:
    static std::shared_ptr<GrayScale> _instance;
};

#endif