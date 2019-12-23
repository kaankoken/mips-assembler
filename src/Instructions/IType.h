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

        void setter(std::vector<std::string>);

        std::pair<int, std::string> findInst(std::string) const;
        std::unordered_map<std::string, std::pair<int, std::string>> getWholeInst() const;
};
