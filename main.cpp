#include <iostream>
#include "CommandsHandler.h"


int main() {
    CommandsHandler hdl = CommandsHandler();
    while (std::cin.getline(hdl.currentCommand, 41)) {
        hdl.handleCommand();
    }
    return 0;
}