#pragma once // Evita che il file venga incluso più volte nello stesso .cpp
#include <string>
#include <filesystem>

namespace fs = std::filesystem;
/*
    Cosa deve fare?
    -   Ricevere il percorso specificato dall'utente da riga di comando
    -   Verificare che la cartella .mimigit esista nella directory corrente
    -   Verificare che il file da aggiungere esista
    -   Creare un oggetto Blob con il contenuto del file e salvarlo su disco
*/
class AddController{
public:
    AddController() = default;

    // Passo il percorso del file come riferimento per evitare duplicazioni di memoria e migliorare le prestazioni
    bool addOperation(const fs::path& filePath);
private:
};