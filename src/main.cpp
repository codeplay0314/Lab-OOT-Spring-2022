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
    shared_ptr<Board> board = make_shared<Board>(20, gscale);

/////////////////////////////////////
    int x1 = 0, y1 = 0;
    int x2 = 19, y2 = 19;
    // cin >> x1 >> y1 >> x2 >> y2;
    Coordinate p1 = Coordinate(x1, y1);
    Coordinate p2 = Coordinate(x2, y2);

    int x = 11, y = 0;
    string str = "!";
    // cin >> x >> y >> str;
    Coordinate p = Coordinate(x, y);

    Coordinate offset1(2, 1);
    vector<shared_ptr<Command>> cmds1;
    cmds1.push_back(ColorCommand::New(board, 200, true));
    cmds1.push_back(LineCommand::New(board, p1, p2));
    cmds1.push_back(TextCommand::New(board, p, str));
    cmds1.push_back(ColorCommand::New(board, color, false));
    shared_ptr<MacroCommand> macro1 = MacroCommand::New(board, offset1, cmds1);
    
    Coordinate offset2 = Coordinate(2, 1);
    vector<shared_ptr<Command>> cmds2;
    cmds2.push_back(macro1->Copy());
    shared_ptr<MacroCommand> tmp = MacroCommand::New(board, offset2, cmds2);
    shared_ptr<Command> macro2 = tmp->Copy();

/////////////////////////////////////
    CommandInvoker invoker(board);

    invoker.Execute(ColorCommand::New(board, color, true));
        invoker.Execute(ShowCommand::New(board));

    invoker.Execute(LineCommand::New(board, p1, p2));
        invoker.Execute(ShowCommand::New(board));

    invoker.Undo();
        invoker.Execute(ShowCommand::New(board));

    invoker.Execute(TextCommand::New(board, p, str));
    invoker.Execute(macro1);
        invoker.Execute(ShowCommand::New(board));

    invoker.Execute(macro2);
        invoker.Execute(ShowCommand::New(board));

    invoker.Execute(LineCommand::New(board, p1, p2));
        invoker.Execute(ShowCommand::New(board));

    invoker.Undo();
        invoker.Execute(ShowCommand::New(board));

    invoker.Undo();
        invoker.Execute(ShowCommand::New(board));

    invoker.Execute(LineCommand::New(board, p1, p2));
        invoker.Execute(ShowCommand::New(board));

    invoker.Undo();
        invoker.Execute(ShowCommand::New(board));

    invoker.Redo();
        invoker.Execute(ShowCommand::New(board));

    return 0;
}
