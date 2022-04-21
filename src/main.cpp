#include <iostream>
#include <vector>
#include "char_lib.h"

int main(int, char**) {
    char c;
    std::cin >> c;
    std::vector<int> shape = getShape(c);
    for (int i = 0; i < 8; i++) {
        for (int j = 7; j >= 0; j--) {
            std::cout << ((shape[i]&(1<<j)) ? '1' : '0');
        }
        std::cout << std::endl;
    }
    return 0;
}
