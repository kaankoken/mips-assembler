#pragma once
#include <iostream>
#include <unordered_map>

class Registers {
    private:
        std::unordered_map<std::string, int> registers;
    public:
        Registers();
        ~Registers();
               
        int findInst(std::string) const;
        std::unordered_map<std::string, int> getWholeInst() const;
};
