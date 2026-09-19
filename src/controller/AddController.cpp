#include "AddController.hpp"
#include "Index.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <Blob.hpp>

namespace fs = std::filesystem;

bool AddController::addOperation(const fs::path& filePath) {
    // Controllare se la cartella .minigit esiste nella directory corrente
    if (!fs::exists(".minigit") || !fs::is_directory(".minigit")) {
        std::cerr << "Errore: la cartella .minigit non esiste nella directory corrente." << std::endl;
        return false;
    }

    // verificare se il file da aggiungere esiste
    if (!fs::exists(filePath) || !fs::is_regular_file(filePath)) {
        std::cerr << "Errore: il file specificato non esiste o non è un file regolare." << std::endl;
        return false;
    }

    // creare un oggetto Blob con il contenuto del file e salvarlo su disco
    std::ifstream inputFile(filePath, std::ios::binary);
    if (!inputFile) {
        std::cerr << "Errore: impossibile aprire il file per la lettura." << std::endl;
        return false;
    }

    Blob blob(std::string((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>()));
    if (!blob.saveToDisk(".minigit")) {
        std::cerr << "Errore: impossibile salvare il blob su disco." << std::endl;
        return false;
    }

    // Aggiornare l'indice con il nuovo blob
    fs::path indexPath = ".minigit/index";
    Index index;
    index.loadFromDisk(indexPath);
    index.addEntry(filePath, blob.getHash());
    if (!index.saveToDisk(indexPath)) {
        std::cerr << "Errore: impossibile salvare l'indice su disco." << std::endl;
        return false;
    }
    
    
    return true;
}