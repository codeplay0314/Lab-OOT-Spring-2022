#include <fstream>
#include "board.h"
#include "draw.h"
#include "command.h"
#include "cmd_parser.h"
#include "cmd_invoker.h"

void run(int argc, char** argv) {
    char* file_name;
    int gscale = 2, gray = 0;

    if (argc == 1) file_name = argv[1];
    else {
        gscale = atoi(argv[2]);
        file_name = argv[3];
    }

    std::shared_ptr<Board> board = std::make_shared<Board>(50, gscale);

    std::string script;
    std::string line;
    std::fstream fin(file_name);

    while (getline(fin, line)) {
        if (line.length() < 2 || line[0] != '/' || line[1] != '/') {
            script += line;
        }
    }

    CommandParser parser;
    std::vector<std::shared_ptr<Command>> cmds = parser.ParseCommands(board, script);
    CommandInvoker invoker(board);
    invoker.Execute(cmds);
}