#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>

class JType {
    private:
        std::unordered_map<std::string, int> jTypeInst;
    public:
        JType();
        ~JType();

        void setter(std::vector<std::string>);

        int findInst(std::string) const;
        std::unordered_map<std::string, int> getWholeInst() const;
};
