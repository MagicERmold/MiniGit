#pragma once

#include <string>
#include <filesystem>

namespace fs = std::filesystem;

class Blob{
    public:
        // Costruttore che accetta il contenuto del file
        // explicit impone di istanziare l'oggetto solo in modo intenzionale, evitando conversioni implicite da std::string a Blob
        explicit Blob(std::string content);

        // Getter con marcatura const per evitare modifiche all'oggetto
        // Restituiamo riferimenti costanti per evitare copie non necessarie e garantire che il contenuto e l'hash non vengano modificati dall'esterno
        const std::string& getContent() const;
        const std::string& getHash() const;

        // Salva il blob dentro .minigit/objects/<hash>
        bool saveToDisk(const fs::path& repoRoot) const;

    private:
        // Attributi privati per memorizzare il contenuto e l'hash del blob
        // Convenzione di C++: gli attributi privati terminano con un underscore per distinguerli dai parametri dei metodi e dalle variabili locali
        std::string content_;
        std::string hash_;

        // Metodo privato per calcolare l'hash del contenuto
        std::string computeHash(const std::string& data) const;
};