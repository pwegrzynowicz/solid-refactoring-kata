#ifndef OCP_COMMAND_H
#define OCP_COMMAND_H

#include <string>
#include <memory>
#include <unordered_map>
#include <iostream>
#include <sstream>
#include <vector>

class Command;

using line_t = std::string;
using command_ptr_t = std::unique_ptr<Command>;
using name_t = std::string;
using value_t = std::string;
using variables_t = std::unordered_map<name_t, value_t>;

class Command {
public:
    virtual ~Command() = default;

    virtual bool matches(line_t const& line) const = 0;

    virtual void execute(line_t const& line, variables_t& variables) = 0;
};

class VariableCommand : public Command {
public:
    bool matches(line_t const& line) const override {
        return line.length() > 0 && line.front() == '$';
    }

    void execute(const line_t& line, variables_t& variables) override {
        // Process the entire line as a variable.
        size_t equals = line.find('=');
        std::string name = line.substr(0, equals);
        std::string value = line.substr(equals + 1);
        variables.insert({name, value});
    }
};

class AddCommand : public Command {
public:
    bool matches(line_t const& line) const override {
        return line.find("!add", 0) == 0;
    }

    void execute(line_t const& line, variables_t& variables) override {
        // Process the add command: add another variable or value to a specified variable.
        std::istringstream iss(line);
        std::vector<std::string> tokens((std::istream_iterator<std::string>(iss)),
                                        std::istream_iterator<std::string>());
        if (tokens.size() == 3 && tokens[1][0] == '$') {
            std::string variableName = tokens[1];
            std::string arg = (tokens[2][0] == '$') ? variables[tokens[2]] : tokens[2];
            variables[variableName] += arg;
        }
    }
};

class PrintCommand : public Command {
public:
    bool matches(line_t const& line) const override {
        return line.find("!print", 0) == 0;
    }

    void execute(line_t const& line, variables_t& variables) override {
        // Process the print command.
        std::istringstream iss(line);
        std::vector<std::string> tokens((std::istream_iterator<std::string>(iss)),
                                        std::istream_iterator<std::string>());
        auto it = tokens.begin();
        it++;
        while (it != tokens.end()) {
            std::string token = *it++;
            if (token[0] == '$') {
                std::cout << variables[token];
            } else {
                std::cout << token;
            }
        }
        std::cout << std::endl;
    }
};

class EmptyCommand : public Command {
public:
    bool matches(line_t const& line) const override { return true; }

    void execute(line_t const& line, variables_t& variables) override {}
};


#endif //OCP_COMMAND_H
