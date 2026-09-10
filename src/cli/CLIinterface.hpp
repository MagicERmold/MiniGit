#pragma once // Evita che il file venga incluso più volte nello stesso .cpp

#include <string_view> // Include la libreria string_view per gestire le stringhe in modo efficiente

// Definisce un enum class per rappresentare le operazioni disponibili
enum class Operation { // Definisce un enum class per rappresentare le operazioni disponibili
    INIT, // Operazione di inizializzazione
    ADD, // Operazione di aggiunta di un file
    STATUS, // Operazione di visualizzazione dello stato
    COMMIT, // Operazione di commit con messaggio
    LOG, // Operazione di visualizzazione del log
    HELP, // Operazione di aiuto
    INVALID // Operazione non valida
};

// Definisce la classe CLIinterface per gestire l'interfaccia a riga di comando
class CLIinterface { // Definisce la classe CLIinterface per gestire l'interfaccia a riga di comando
public: // Sezione pubblica della classe
    // Costruttore di default
    CLIinterface() = default;

    // Metodo principale che avvia la CLI
    int run(int argc, char* argv[]); // Dichiarazione del metodo run che prende in input il numero di argomenti e l'array di argomenti

private: // Sezione privata della classe
    // Metodo ausiliario interno per convertire la stringa dell'operazione in un enum Operation
    Operation parseOperation(std::string_view operation); // Dichiarazione del metodo parseOperation che prende in input una stringa e restituisce un enum Operation
}; // ATTENZIONE: in C++ serve il punto e virgola ';' dopo la chiusura della classe!