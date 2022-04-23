#include <memory>
#include <vector>
#include <iostream>
#include "board.h"
#include "command.h"
#include "cmd_invoker.h"
using namespace std;

int main(int, char**) {

    int gscale = 256, color = 128;
    // cin >> gscale >> color;

    shared_ptr<Board> board = Board::Instance(20, gscale);
    CommandInvoker invoker(board);

    ColorCommand colorc = ColorCommand(color);
    invoker.Execute(colorc);

    ShowCommand showc;
    invoker.Execute(showc);

    int x1 = 0, y1 = 0;
    int x2 = 19, y2 = 19;
    // cin >> x1 >> y1 >> x2 >> y2;
    Coordinate p1 = Coordinate(x1, y1);
    Coordinate p2 = Coordinate(x2, y2);
    LineCommand linec = LineCommand(p1, p2);
    // invoker->Execute(line);

    int x = 11, y = 0;
    string str = "!";
    // cin >> x >> y >> str;
    Coordinate p = Coordinate(x, y);
    TextCommand textc = TextCommand(p, str);
    // invoker->Execute(text);
    
    string name = "macro1";
    Coordinate offset(0, 1);
    vector<shared_ptr<Command>> cmds;
    cmds.push_back(make_shared<LineCommand>(linec));
    cmds.push_back(make_shared<TextCommand>(textc));
    cmds.push_back(make_shared<ShowCommand>(showc));
    MacroCommand macro1(name, offset, cmds);
    invoker.Execute(macro1);

    name = "macro2";
    offset = Coordinate(2, 1);
    cmds.clear();
    cmds.push_back(make_shared<ColorCommand>(200));
    cmds.push_back(make_shared<MacroCommand>(macro1));
    MacroCommand macro2(name, offset, cmds);
    invoker.Execute(macro2);

    return 0;
}
