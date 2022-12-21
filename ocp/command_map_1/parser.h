#ifndef OCP_PARSER_H
#define OCP_PARSER_H

#include <unordered_map>
#include "command.h"

class Parser {
    using commands_t = std::unordered_map<token_t, command_ptr_t>;

    commands_t commands;
    command_ptr_t defaultCommand;
    variables_t variables;

    static token_t findWord(line_t const& line) {
        // search for a space from the index 1 inclusive
        auto found = line.find(' ', 1);
        if (found != std::string::npos) {
            return line.substr(0, found);
        }
        return {};
    }

    static token_t findFirstChar(line_t const& line) {
        if (line.length() > 0) {
            // 1-char long substring
            return line.substr(0, 1);
        }
        return {};
    }

    static token_t findToken(line_t const& line) {
        auto word = findWord(line);
        if (!word.empty()) {
            return word;
        }
        return findFirstChar(line);
    }

    Command& findCommand(token_t const& token) {
        try {
            return *commands.at(token);
        } catch (std::out_of_range const& ex) {
            return *defaultCommand;
        }
    }

    void process(line_t const& line) {
        token_t token = findToken(line);
        Command& cmd = findCommand(token);
        cmd.execute(line, variables);
    }

public:
    Parser() : defaultCommand(std::make_unique<EmptyCommand>()) {}

    Parser& addCommand(token_t const& token, command_ptr_t command) {
        if (command) {
            commands[token] = std::move(command);
        }
        return *this;
    }

    void parse() {
        variables.clear();
        line_t line;
        while (std::getline(std::cin, line)) {
            process(line);
        }
    }
};

#endif //OCP_PARSER_H
