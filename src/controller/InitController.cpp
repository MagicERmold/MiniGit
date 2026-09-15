#include "InitController.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>

// Uso fs per non riscrivere ogni volta std::filesystem
namespace fs = std::filesystem;

/*
    This class aims to initialize the operation: "INIT". This method operates in the following order:
    -   Checks if an hidden folder ./minigit exists
*/
int InitController::initOperation(){
    // Inizializzo il nome del path da creare
    fs::path repo_path = ".minigit";
    // Devo controllare se esiste il path
    if(fs::exists(repo_path)){
        std::cout << "Repository MiniGit già inizializzata in questo percorso!\n";
        return 0;
    }

    // Se non esiste la creo .minigit/objects
    fs::create_directories(repo_path / "objects");

    std::cout << "Inizializzo repository Minigit vuoto in "
              << fs::absolute(repo_path) << "\n";           // restituisce il percorso completo
    
    return 0;
}