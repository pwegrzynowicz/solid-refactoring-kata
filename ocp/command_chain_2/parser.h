#ifndef OCP_PARSER_H
#define OCP_PARSER_H

#include <vector>
#include "command.h"

class Parser {
    using commands_t = std::vector<command_ptr_t>;

    commands_t commands;
    command_ptr_t defaultCommand;
    variables_t variables;

    void process(std::string const& line) {
        for (auto& command: commands) {
            if (command->tryExecute(line, variables)) {
                return;
            }
        }
        defaultCommand->tryExecute(line, variables);
    }

public:
    Parser() : defaultCommand(std::make_unique<EmptyCommand>()) {}

    Parser& addCommand(command_ptr_t command) {
        if (command) {
            commands.push_back(std::move(command));
        }
        return *this;
    }

    void parse() {
        line_t line;
        while (std::getline(std::cin, line)) {
            process(line);
        }
    }
};

#endif //OCP_PARSER_H
