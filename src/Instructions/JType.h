#pragma once
#include <iostream>
#include <unordered_map>

class JType {
    private:
        std::unordered_map<std::string, std::pair<int, int>> jTypeInst;
    public:
        JType();
        ~JType();
               
        std::pair<int, int> findInst(std::string) const;
        std::unordered_map<std::string, std::pair<int, int>> getWholeInst() const;
};
