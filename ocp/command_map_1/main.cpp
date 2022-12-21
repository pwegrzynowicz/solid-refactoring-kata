#include "parser.h"

int main() {
    Parser parser;
    parser
            .addCommand("$", std::make_unique<VariableCommand>())
            .addCommand("!print", std::make_unique<PrintCommand>())
            .addCommand("!add", std::make_unique<AddCommand>());
    parser.parse();
    return 0;
}
