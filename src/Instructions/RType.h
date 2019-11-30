#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>
#include <cstring>
class RType {
    private:
        std::unordered_map<std::string, std::tuple<int, int, int>> rTypeInst;
    
    public:
        RType();
        ~RType();
               
        std::tuple<int, int, int> findInst(std::string) const;
        std::unordered_map<std::string, std::tuple<int, int, int>> getWholeInst() const;
        std::string fieldChecker(std::vector<std::string>);
};
