#include <iostream>
#include <vector>
#include <memory>
#include "board.h"
using namespace std;

int main(int, char**) {
    shared_ptr<Board> board = Board::Instance();
    board->show();
    return 0;
}
