#pragma once
#include <iostream>
#include <unordered_map>

class RType {
    private:
        std::unordered_map<std::string, std::tuple<int, int, std::string>> rTypeInst;
    public:
        RType();
        ~RType();
               
        std::tuple<int, int, std::string> findInst(std::string) const;
        std::unordered_map<std::string, std::tuple<int, int, std::string>> getWholeInst() const;
};
