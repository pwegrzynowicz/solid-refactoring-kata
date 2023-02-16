#include <iostream>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <string>
#include <iterator>

// A simple parser that processes different commands e.g.
// - defining a variable
// - printing a string or a variable
// - adding a string to a variable (concatenation)
int main() {
    std::unordered_map<std::string, std::string> variables;
    std::string line;
    while (std::getline(std::cin, line)) {
        switch (line[0]) {
            case '$': {
                // Process an entire line as a variable.
                size_t equals = line.find('=');
                std::string name = line.substr(0, equals);
                std::string value = line.substr(equals+1);
                variables.insert({name, value});
                break;
            }
            case '!': {
                // Process an action in this line.
                if (line.find("!print", 0) == 0) {
                    // Process the print action.
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

                } else if (line.find("!add", 0) == 0) {
                    // Process the add action: add another variable or value to a specified variable.
                    std::istringstream iss(line);
                    std::vector<std::string> tokens((std::istream_iterator<std::string>(iss)),
                                                     std::istream_iterator<std::string>());
                    if (tokens.size() == 3 && tokens[1][0] == '$') {
                        std::string variableName = tokens[1];
                        std::string arg = (tokens[2][0] == '$') ? variables[tokens[2]] : tokens[2];
                        variables[variableName] += arg;
                    }
                }
                break;
            }
            default: {
                // Do nothing.
            }
        }
    }
    return 0;
}
