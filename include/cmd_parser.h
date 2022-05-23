#ifndef _CMD_PARSER_H_
#define _CMD_PARSER_H_

#include <map>

class CommandParser {
public:
    std::vector<std::shared_ptr<Command>> ParseCommands(std::shared_ptr<Board> board, std::string& str);
private:
    void RegisterMacroCommand(std::string& cmd, std::shared_ptr<Board> board);
    std::shared_ptr<Command> GetCommand(std::string& cmd, std::shared_ptr<Board> board);
    std::shared_ptr<Command> GetMacroCommand(std::string& cmd, const Coordinate& offset);
    std::map<std::string, std::shared_ptr<MacroCommand>> _macro_table;
};



#endif