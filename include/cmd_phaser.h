#ifndef _CMD_PHASER_H_
#define _CMD_PHASER_H_

#include <map>

class CommandPhaser {
public:
    vector<shared_ptr<Command>> PharseCommands(shared_ptr<Board> board, string& str);
private:
    void RegisterMacroCommand(string& cmd, shared_ptr<Board> board);
    shared_ptr<Command> GetCommand(string& cmd, shared_ptr<Board> board);
    shared_ptr<Command> GetMacroCommand(string& cmd, const Coordinate& offset);
    map<string, shared_ptr<MacroCommand>> _macro_table;
};



#endif