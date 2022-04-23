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

    int x1 = 0, y1 = 0, x2 = 9, y2 = 9;
    cin >> x1 >> y1 >> x2 >> y2;

    Coordinate p1 = Coordinate(x1, y1);
    Coordinate p2 = Coordinate(x2, y2);
    LineCommand line = LineCommand(board, p1, p2);
    invoker->Execute(line);

    int x = 0, y = 0;
    string str = "0";
    cin >> x >> y >> str;
    Coordinate p = Coordinate(x, y);
    TextCommand text = TextCommand(board, p, str);
    invoker->Execute(text);
    
    board->Show();
    return 0;
}
