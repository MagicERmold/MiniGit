#include <iostream>
#include "CLIinterface.hpp" // Include the header file for the CLI interface

// Entry point of the program
// @param argc Number of command-line arguments
// @param argv Array of command-line arguments
// @return Exit status of the program
// Should do this operations:
//  -   minigit init
//  -   minigit add <file>
//  -   minigit status
//  -   minigit commit -m "..."
//  -   minigit log
int main(int argc, char* argv[]) {
    // Check if the user provided a valid operation
    // Use && instead of || to ensure that the user provided a valid operation
    // || is always true if the first condition is true, so we need to use && to ensure that the user provided a valid operation
    if(argc < 2 || (argv[1] != std::string("help") && argv[1] != std::string("init") && argv[1] != std::string("add") && argv[1] != std::string("status") && argv[1] != std::string("commit") && argv[1] != std::string("log"))) {
        std::cerr << "Usage: " << argv[0] << " <operation>" << std::endl;
        std::cerr << "Select a valid operation: init, add, status, commit, log" << std::endl;
        std::cerr << "Select help for more information: " << argv[0] << " help" << std::endl;
        return 1;
    }

    // Create an instance of the CLIinterface class
    CLIinterface cli; // Create an instance of the CLIinterface class
    cli.run(argc, argv);

    return 0;
}