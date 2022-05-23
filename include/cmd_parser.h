#ifndef _CMD_PARSER_H_
#define _CMD_PARSER_H_

#include <map>

class CommandParser {
public:
    vector<shared_ptr<Command>> ParseCommands(shared_ptr<Board> board, string& str);
private:
    void RegisterMacroCommand(string& cmd, shared_ptr<Board> board);
    shared_ptr<Command> GetCommand(string& cmd, shared_ptr<Board> board);
    shared_ptr<Command> GetMacroCommand(string& cmd, const Coordinate& offset);
    map<string, shared_ptr<MacroCommand>> _macro_table;
};



#endif