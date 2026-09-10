#include "CLIinterface.hpp" // Include the header file for the CLI interface
#include <iostream> // Include the iostream library for input/output operations

// Define the parseOperation method to convert a string to an Operation enum
Operation CLIinterface::parseOperation(std::string_view operation) { // Define the parseOperation method to convert a string to an Operation enum
    if (operation == "init") { // Check if the operation is "init"
        return Operation::INIT; // Return the INIT enum value
    } else if (operation == "add") { // Check if the operation is "add"
        return Operation::ADD; // Return the ADD enum value
    } else if (operation == "status") { // Check if the operation is "status"
        return Operation::STATUS; // Return the STATUS enum value
    } else if (operation == "commit") { // Check if the operation is "commit"
        return Operation::COMMIT; // Return the COMMIT enum value
    } else if (operation == "log") { // Check if the operation is "log"
        return Operation::LOG; // Return the LOG enum value
    } else if (operation == "help") { // Check if the operation is "help"
        return Operation::HELP; // Return the HELP enum value
    } else { // If none of the above, it's an invalid operation
        return Operation::INVALID; // Return the INVALID enum value
    }
}

int CLIinterface::run(int argc, char* argv[]){
    // Qui andrà la logica con i controlli e lo switch case per le operazioni
}

