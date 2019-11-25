#pragma once
#include <iostream>
#include <unordered_map>

class IType {
    private:
        std::unordered_map<std::string, std::pair<int, int>> iTypeInst;
    public:
        IType();
        ~IType();
               
        std::pair<int, int> findInst(std::string) const;
        std::unordered_map<std::string, std::pair<int, int>> getWholeInst() const;
};
