#include <memory>
#include <vector>
#include <iostream>
#include "board.h"
#include "command.h"
using namespace std;

int main(int, char**) {
    shared_ptr<Board> board = Board::Instance();
    shared_ptr<CommandInvoker> invoker = CommandInvoker::Instance();

    board->Show();

    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;

    vector<int> args = {x1, y1, x2, y2};
    LineCommand line = LineCommand(board, args);
    invoker->Execute(line);
    
    board->Show();
    return 0;
}
