#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>
#include <cstring>
class IType {
    private:
        std::unordered_map<std::string, std::pair<int, std::string>> iTypeInst;
    public:
        IType();
        ~IType();
               
        std::pair<int, std::string> findInst(std::string) const;
        std::unordered_map<std::string, std::pair<int, std::string>> getWholeInst() const;
        std::string fieldChecker(std::vector<std::string>);
};
