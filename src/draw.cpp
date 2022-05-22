#include <memory>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "board.h"
#include "draw.h"
#include "command.h"
#include "cmd_phaser.h"
#include "cmd_invoker.h"
using namespace std;

void run(int argc, char** argv) {
    char* file_name;
    int gscale = 2, gray = 0;

    if (argc == 1) file_name = argv[1];
    else {
        gscale = atoi(argv[2]);
        file_name = argv[3];
    }

    shared_ptr<Board> board = make_shared<Board>(50, gscale);

    string script;
    string line;
    fstream fin(file_name);

    while (getline(fin, line)) {
        if (line.length() < 2 || line[0] != '/' || line[1] != '/') {
            script += line;
        }
    }

    CommandPhaser phaser;
    vector<shared_ptr<Command>> cmds = phaser.PharseCommands(board, script);
    CommandInvoker invoker(board);
    invoker.Execute(cmds);
}