#pragma once
#include <iostream>
#include <unordered_map>

class JType {
    private:
        std::unordered_map<std::string, int> jTypeInst;
    public:
        JType();
        ~JType();
               
        int findInst(std::string) const;
        std::unordered_map<std::string, int> getWholeInst() const;
};
