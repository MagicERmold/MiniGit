#pragma once
#include <string>
#include <filesystem>
#include <map>

namespace fs = std::filesystem;
/*
    Cosa deve fare questa classe?
    - Ha bisogno di una struttura dati per memorizzare le corrispondenze percoso -> hash. Inoltre deve aggiornare l'hash se il file viene aggiornato.
    - Dobbiamo poter leggere la struttura dati, quando ad esempio vogliamo aggiornare il file oppure conoscere lo status del file.
    - Dobbiamo poter scrivere la struttura dati, quando ad esempio vogliamo aggiornare il file oppure conoscere lo status del file.
*/

class Index{
    public:
        // Costruttore di default
        Index() = default;

        // Metodo per caricare lo stato da disco
        bool loadFromDisk(const fs::path& filePath);

        // Metodo per aggiungere o aggiornare una voce
        void addEntry(const fs::path& filePath, const std::string& hash);

        // Metodo per salvare lo stato su disco
        bool saveToDisk(const fs::path& filePath) const;

        // Metodo per recuperare le voci dell'indice, senza modificare la lista evitando copie non necessarie
        const std::map<fs::path, std::string>& getEntries() const;
    private:
        // Struttura dati per memorizzare le corrispondenze percorso -> hash
        std::map<fs::path, std::string> indexEntries_;
};