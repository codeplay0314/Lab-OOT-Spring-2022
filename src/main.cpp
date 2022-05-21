#include <memory>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "board.h"
#include "command.h"
#include "cmd_phaser.h"
#include "cmd_invoker.h"
using namespace std;

int main(int argc, char** argv) {
    char* file_name;
    int gscale = 2, gray = 0;

    if (argc == 1) file_name = argv[1];
    else {
        gscale = atoi(argv[2]);
        file_name = argv[3];
    }

    shared_ptr<Board> board = make_shared<Board>(51, gscale);

    string script;
    string line;
    fstream fin(file_name);
    // fstream fin("run/testcases/script1.txt");
    while (getline(fin, line)) {
        if (line.length() < 2 || line[0] != '/' || line[1] != '/') {
            script += line;
        }
    }

    CommandPhaser phaser;
    vector<shared_ptr<Command>> cmds = phaser.PharseCommands(board, script);
    CommandInvoker invoker(board);
    invoker.Execute(cmds);
    
    return 0;
}

void Test() {
    int gscale = 256, color = 128;
    // cin >> gscale >> color;
    shared_ptr<Board> board = make_shared<Board>(20, gscale);

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
    string name = "macro1";
    shared_ptr<MacroCommand> macro1 = MacroCommand::New(board, name, offset1, cmds1);
    
    Coordinate offset2 = Coordinate(2, 1);
    vector<shared_ptr<Command>> cmds2;
    cmds2.push_back(macro1->Copy());
    name = "macro2";
    shared_ptr<MacroCommand> tmp = MacroCommand::New(board, name, offset2, cmds2);
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
}