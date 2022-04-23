#include <vector>
#include "asciis.h"
#include "char_lib.h"

std::vector<int> GetCharShape(char c) {
    std::vector<int> shape(8);
    if (c < 32 || c > 128) return shape;
    c -= 32;
    for (int i = 0; i < 8; i++) shape[i] = nAsciiDot[c * 8 + i];
    return shape;
}