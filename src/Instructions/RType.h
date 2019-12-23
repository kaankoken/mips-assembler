#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>
#include <cstring>
class RType {
    private:
        std::unordered_map<std::string, std::tuple<int, int, std::string>> rTypeInst;
    public:
        RType();
        ~RType();
        
        void setter(std::vector<std::string>);

        std::tuple<int, int, std::string> findInst(std::string) const;
        std::unordered_map<std::string, std::tuple<int, int, std::string>> getWholeInst() const;
};
