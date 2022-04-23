#include "gray_scale.h"

// BW2Scale
shared_ptr<GrayScale> BW2Scale::_instance;

shared_ptr<GrayScale> BW2Scale::Instance() {
    if (!_instance) _instance = make_shared<BW2Scale>();
    return _instance;
}

int BW2Scale::GetColor(int gray) {
    return !!gray;
}

// BW256Scale
shared_ptr<GrayScale> BW256Scale::_instance;

shared_ptr<GrayScale> BW256Scale::Instance() {
    if (!_instance) _instance = make_shared<BW256Scale>();
    return _instance;
}

int BW256Scale::GetColor(int gray) {
    return gray * 10 / 256;
}