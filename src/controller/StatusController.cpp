#include "StatusController.hpp"
#include "Index.hpp"
#include "Blob.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <map>
#include <string>
#include <vector>


/*
    -   Verificare che la cartella .minigit esista nella directory corrente.
    -   Recuperare lo stato dei file
    -   Verificare quali stati dei file sono stati aggiunti e stampare a schermo i file aggiunti e aggiornati come prima schermata
    -   Verificare quali stati dei file sono stati modificati e stampare a schermo i file modificati come seconda schermata
    -   Verificare quali stati dei file NON sono stati aggiunti e stampare a schermo i file non aggiunti come terza schermata
*/

std::map<std::string, std::string> StatusController::getFileStatus() {
    std::map<std::string, std::string> fileStatus;

    // Recupero le voci dell'indice
    Index index;
    index.loadFromDisk(".minigit/index");
    const auto& indexEntries = index.getEntries();

    // Itero sui file nella directory corrente
    for (const auto& entry : fs::recursive_directory_iterator(fs::current_path())) {
        if (entry.is_regular_file()) {
            fs::path relativePath = fs::relative(entry.path());
            
            // Dobbiamo controllare che non abbiamo passato .minigit o .git come file da controllare, altrimenti andremmo in un loop infinito
            if (relativePath.string().find(".minigit") == 0 || relativePath.string().find(".git") == 0) {
                continue; // Salta i file all'interno delle cartelle .minigit e .git
            }
            
            // Dobbiamo leggere il contenuto del file e passarlo al Blob per calcolare l'hash
            std::ifstream fileStream(relativePath);
            if (!fileStream) {
                std::cerr << "Errore: impossibile aprire il file " << relativePath << std::endl;
                continue;
            }
            std::string fileContent((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());
            Blob blob(fileContent);
            
            std::string currentHash = blob.getHash(); // Calcolo l'hash del file corrente

            // Controllo se il file è presente nell'indice
            auto it = indexEntries.find(relativePath.string());
            if (it != indexEntries.end()) {
                // Il file è presente nell'indice, verifico se è stato modificato
                if (it->second == currentHash) {
                    fileStatus[relativePath] = "added"; // Aggiunto
                } else {
                    fileStatus[relativePath] = "modified"; // Modificato
                }
            } else {
                // Il file non è presente nell'indice, quindi è stato aggiunto
                fileStatus[relativePath] = "not added"; // Non aggiunto
            }
        }
    }

    return fileStatus;
}


bool StatusController::statusOperation(){
    // Verifico che la cartella .minigit esista nella directory corrente
    if(!std::filesystem::exists(".minigit")){
        std::cerr << "Errore: la cartella .minigit non esiste nella directory corrente. Esegui prima l'operazione 'init'." << std::endl;
        return false;
    }

    // Recupero lo stato dei file
    std::map<std::string, std::string> fileStatus = getFileStatus();

    // Verifico quali stati dei file sono stati aggiunti e stampo a schermo i file aggiunti e aggiornati come prima schermata
    std::cout << "\033[0m" << "File aggiunti o aggiornati:" << std::endl;
    for(const auto& [relativePath, status] : fileStatus){
        if(status == "added"){
            std::cout << "\033[32m" << "\t" << relativePath << " - " << status << std::endl;
        }
    }

    // Verifico quali stati dei file sono stati modificati e stampo a schermo i file modificati come seconda schermata
    std::cout << "\033[0m" << "\nFile modificati:" << std::endl;
    for(const auto& [relativePath, status] : fileStatus){
        if(status == "modified"){
            std::cout << "\033[33m" << "\t" << relativePath << " - " << status << std::endl;
        }
    }

    // Verifico quali stati dei file NON sono stati aggiunti e stampo a schermo i file non aggiunti come terza schermata
    std::cout << "\033[0m" << "\nFile non aggiunti:" << std::endl;
    for(const auto& [relativePath, status] : fileStatus){
        if(status == "not added"){
            std::cout << "\033[31m" << "\t" << relativePath << " - " << status << std::endl;
        }
    }

    std::cout << "\033[0m"; // Reset del colore del testo
    return true;
}