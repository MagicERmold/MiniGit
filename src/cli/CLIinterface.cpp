#include "CLIinterface.hpp" // Include the header file for the CLI interface
#include "InitController.hpp" // Include the header file for the Init Controller
#include "AddController.hpp"
#include "StatusController.hpp"
#include "CommitController.hpp"
#include "LogController.hpp"
#include "HelpController.hpp"
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

// Usare le graffe è una buona pratica quando si dichiarano variabili locali all'interno dello switch per evitare problemi di scope
int CLIinterface::run(int argc, char* argv[]){
    // Qui andrà la logica con i controlli e lo switch case per le operazioni
    Operation op = parseOperation(argv[1]);

    switch (op)
    {
    case Operation::INIT:
        InitController ic;
        ic.initOperation();
        break;
    // Operazione ADD per aggiungere un file al repository .minigit
    case Operation::ADD: {
        AddController ac;
        
        // Controllo se l'utente ha passato almeno un file da aggiungere
        if (argc < 3) {
            std::cerr << "Errore: nessun file specificato per l'operazione 'add'." << std::endl;
            return 1; // Restituisco un codice di errore
        }

        // Controllo se l'utente ha passato "." come argomento per aggiungere tutti i file nella directory corrente
        if(std::string(argv[2]) == "."){
            // Devo aggiungere tutti i file nella directory corrente
            for (const auto& entry : fs::directory_iterator(fs::current_path())) {
                if (entry.is_regular_file()) {
                    // fs::relative converte il percorso assoluto in relativo alla cartella corrente
                    ac.addOperation(fs::relative(entry.path()));
                }
            }
        } else {
            // Aggiungo i file specificati come argomenti
            for(int i = 2; i < argc; ++i) {
                ac.addOperation(argv[i]);
            }
        }
        
        break;
}
    case Operation::STATUS:
        StatusController sc;
        sc.statusOperation();
        break;
    case Operation::COMMIT:
        CommitController cc;
        cc.commitOperation();
        break;
    case Operation::LOG:
        LogController lc;
        lc.logOperation();
        break;
    case Operation::HELP:
        HelpController hc;
        hc.helpOperation();
        break;
    case Operation::INVALID:
        /* code */
        break;
    default:
        break;
    }

    return 0;
}

