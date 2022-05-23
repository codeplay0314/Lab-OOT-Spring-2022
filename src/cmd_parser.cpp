#include <map>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include "command.h"
#include "cmd_parser.h"

#include <iostream>

vector<string> SplitCommand(const string& cmd) {
    vector<string> cmds;
    bool inmacro = false;
    bool instring = false;
    for (int l = 0, r = 0, undo, redo; l < cmd.length(); r++) {
        if (r - l == 0) {
            undo = cmd[r] == 'u';
            redo = cmd[r] == 'r';
        } else if (r - l == 1) {
            undo += cmd[r] == 'n';
            redo += cmd[r] == 'e';
        } else if (r - l == 2) {
            undo += cmd[r] == 'd';
            redo += cmd[r] == 'd';
        } else if (r - l == 3) {
            undo += cmd[r] == 'o';
            redo += cmd[r] == 'o';
        }

        if (cmd[r] == '"') instring ^= 1; 
        if (instring) continue;
        
        if (cmd[r] == '}') {
            cmds.push_back(cmd.substr(l, r - l + 1));
            l = r + 1;
            inmacro = false;
        } else if (cmd[r] == '#') {
            inmacro = true;
        } else if (!inmacro && (cmd[r] == ')' || undo == 4 || redo == 4)) {
            cmds.push_back(cmd.substr(l, r - l + 1));
            l = r + 1;
        }
    }
    return cmds;
}

vector<string> TrimCommand(const string& cmd) {
    vector<string> res;
    int l = 0, r = 0;
    while (r < cmd.length() && cmd[r] != '(') r++;
    res.push_back(cmd.substr(l, r));
    l = ++r;
    while (r < cmd.length()) {
        if (cmd[r] == ',' || cmd[r] == ')') {
            res.push_back(cmd.substr(l, r - l));
            l = r + 1;
        }
        r++;
    }
    return res;
}

vector<shared_ptr<Command>> CommandParser::ParseCommands(shared_ptr<Board> board, string& str) {
    vector<shared_ptr<Command>> res;

    // Remove whitespaces
    str.erase(remove_if(str.begin(), str.end(), ::isspace), str.end());

    vector<string> cmds = SplitCommand(str);
    
    for (string cmd : cmds) {
        if (cmd[0] == '#') {
            RegisterMacroCommand(cmd, board);
        } else {
            res.push_back(GetCommand(cmd, board));
        }
    }

    return res;
}

void CommandParser::RegisterMacroCommand(string& cmd, shared_ptr<Board> board) {
    int len = cmd.length();
    int l, r;
    for (int i = 1; i < len; i++) {
        if (cmd[i] == '{') l = i;
        if (cmd[i] == '}') r = i;
    }
    vector<string> strs = SplitCommand(cmd.substr(l + 1, r - l - 1));
    vector<shared_ptr<Command>> cmds;
    for (string str : strs) {
        cmds.push_back(GetCommand(str, board));
    }
    string name = cmd.substr(1, l - 1); 
    _macro_table[name] = MacroCommand::New(board, name, Coordinate(0, 0), cmds);
}

shared_ptr<Command> CommandParser::GetMacroCommand(string& cmd, const Coordinate& offset) {
    return _macro_table[cmd]->Copy(offset);
}

shared_ptr<Command> CommandParser::GetCommand(string& cmd, shared_ptr<Board> board) {
    vector<string> tokens = TrimCommand(cmd);
    if (tokens[0] == "color") {
        return ColorCommand::New(board, atoi(tokens[1].c_str()), true);
    } else if (tokens[0] == "line") {
        Coordinate p1 = Coordinate(atoi(tokens[1].c_str()), atoi(tokens[2].c_str()));
        Coordinate p2 = Coordinate(atoi(tokens[3].c_str()), atoi(tokens[4].c_str()));
        return LineCommand::New(board, p1, p2);
    } else if (tokens[0] == "text") {
        Coordinate p = Coordinate(atoi(tokens[1].c_str()), atoi(tokens[2].c_str()));
        return TextCommand::New(board, p, tokens[3].substr(1, tokens[3].size() - 2));
    } else if (tokens[0] == "undo") {
        return Command::New(CommandType::UNDO);
    } else if (tokens[0] == "redo") {
        return Command::New(CommandType::REDO);             
    } else {
        Coordinate p = Coordinate(atoi(tokens[1].c_str()), atoi(tokens[2].c_str()));
        if (tokens[0][0] == '!') tokens[0] = tokens[0].substr(1, cmd.size() - 1);
        return GetMacroCommand(tokens[0], p);
    }
}
