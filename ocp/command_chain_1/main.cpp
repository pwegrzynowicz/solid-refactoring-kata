#include "parser.h"

int main() {
    Parser parser;
    parser
            .addCommand(std::make_unique<VariableCommand>())
            .addCommand(std::make_unique<PrintCommand>())
            .addCommand(std::make_unique<AddCommand>());
    parser.parse();
    return 0;
}
