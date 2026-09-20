#include "Blob.hpp"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <openssl/evp.h> // Include per la libreria OpenSSL, necessaria per il calcolo dell'hash SHA-256

// Costruttore: inizializza il contenuto del blob e calcola l'hash corrispondente
Blob::Blob(std::string content) 
    : content_(std::move(content)) {
    // Calcola l'hash del contenuto e lo memorizza
    hash_ = computeHash(content_);
    }

// Getter per ottenere il contenuto del blob
const std::string& Blob::getContent() const {
    return content_;
}

// Getter per ottenere l'hash del blob
const std::string& Blob::getHash() const {
    return hash_;
}

// Salva il blob su disco nella directory .minigit/objects/<hash>
bool Blob::saveToDisk(const fs::path& repoRoot) const {
    fs::path objectPath = repoRoot / "objects" / hash_;

    // Se l'oggetto esiste già, non fare nulla
    if (fs::exists(objectPath)) {
        return true;
    }

    // Creo un file binario per scrivere il contenuto del blob
    // Uso std::ios::binary per assicurarmi che il contenuto venga scritto correttamente, specialmente se contiene caratteri non testuali (soprattutto su Windows)
    std::ofstream outFile(objectPath, std::ios::binary);

    // Controllo se il file è stato aperto correttamente
    if (!outFile.is_open()){
        std::cerr << "Errore nella scrittura del blob: " << objectPath << "\n";
        return false;
    }

    // Scrivo il contenuto del blob nel file
    outFile << content_;
    // Quando outFile esce dallo scope, il file viene chiuso automaticamente grazie al RAII (Resource Acquisition Is Initialization) di C++.
    return true;
}

// Qui si invoca la funzione di hashing SHA-256 per calcolare l'hash del contenuto
std::string Blob::computeHash(const std::string& data) const {
    // Creiamo il contesto crittografico di OpenSSL
    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    if(!ctx) return ""; // Se non riesce a creare il contesto, ritorna una stringa vuota

    // Inizializziamo l'algoritmo di hashing SHA-256
    if(EVP_DigestInit_ex(ctx, EVP_sha256(), nullptr) != 1) {
        EVP_MD_CTX_free(ctx);
        return ""; // Se fallisce l'inizializzazione, ritorna una stringa vuota
    }

    // Passiamo i byte del dato al digest
    if(EVP_DigestUpdate(ctx, data.data(), data.size()) != 1) {
        EVP_MD_CTX_free(ctx);
        return ""; // Se fallisce l'aggiornamento del digest, ritorna una stringa vuota
    }

    // Estraiamo il risultato binario (32 byte per SHA-256)
    unsigned char hashBytes[EVP_MAX_MD_SIZE];
    unsigned int hashLen = 0;
    if(EVP_DigestFinal_ex(ctx, hashBytes, &hashLen) != 1) {
        EVP_MD_CTX_free(ctx);
        return ""; // Se fallisce l'estrazione del digest, ritorna una stringa vuota
    }

    // Liberiamo la memoria allocata da OpenSSL per il contesto
    EVP_MD_CTX_free(ctx);

    // Convertiamo il risultato binario in una stringa esadecimale leggibile
    std::ostringstream hexStream;
    for(unsigned int i = 0; i < hashLen; ++i) {
        hexStream << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hashBytes[i]);
    }

    return hexStream.str();
}