#pragma once // Evita che il file venga incluso più volte nello stesso .cpp

#include <filesystem>
#include <map>

class StatusController{
public:
    StatusController() = default;

    bool statusOperation();
private:
    std::map<std::string, std::string> getFileStatus();
};