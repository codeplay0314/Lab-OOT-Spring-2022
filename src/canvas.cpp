#include "canvas.h"

shared_ptr<Canvas::canvas> Canvas::get() {
    return _ptr;
}