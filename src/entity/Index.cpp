#include "Index.hpp"
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

// Metodo per aggiungere o aggiornare una voce nell'indice
void Index::addEntry(const fs::path& filePath, const std::string& hash) {
    indexEntries_[filePath] = hash;
}

// Metodo per caricare lo stato da disco
bool Index::loadFromDisk(const fs::path& filePath) {
    // Svuotiamo sempre la mappa prima di caricare nuovi dati
    indexEntries_.clear();

    // Se il file non esiste ancora (es. primo add in una repo nuova),
    // non è un errore: l'indice è semplicemente vuoto!
    if (!fs::exists(filePath)) {
        return true; 
    }

    // Se il file esiste ma non riusciamo ad aprirlo (es. problemi di permessi), allora è un errore
    std::ifstream inFile(filePath);
    if (!inFile.is_open()) {
        return false;
    }

    // Leggo le voci dal file e le inserisco nella mappa
    std::string line;
    while (std::getline(inFile, line)) {
        // Ogni riga dovrebbe essere nel formato "percorso hash"
        size_t spacePos = line.find(' ');
        if (spacePos != std::string::npos) {
            fs::path path = line.substr(0, spacePos);
            std::string hash = line.substr(spacePos + 1);
            indexEntries_[path] = hash;
        }
    }
    return true;
}

// Metodo per salvare lo stato su disco
bool Index::saveToDisk(const fs::path& filePath) const {
    // Apro il file in modalità scrittura
    std::ofstream outFile(filePath);
    if (!outFile.is_open()) {
        return false; // Se non riesco ad aprire il file, ritorno false
    }

    // Scrivo le voci nella mappa nel file
    for (const auto& entry : indexEntries_) {
        outFile << entry.first.string() << ' ' << entry.second << '\n';
    }

    return true;
}

// Metodo per recuperare le voci dell'indice
const std::map<fs::path, std::string>& Index::getEntries() const {
    return indexEntries_;
}