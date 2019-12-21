#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>

class Pseudo {
    private:
        std::unordered_map<std::string, std::vector<std::string>> pseudoInst;
        std::vector<std::string> splitInst (std::string) const;
        std::string replaceStrings(std::string, std::string, size_t) const;
    public:
        Pseudo();
        ~Pseudo();
    
        std::unordered_map<std::string, std::vector<std::string>> getWholeInst() const;
        std::vector<std::string> convertInstructions(std::vector<std::string>);
};