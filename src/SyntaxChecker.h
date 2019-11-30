#pragma once

#include <iostream>
#include <cstring>
#include <vector>
#include <bitset>
#include <stack> 
#include "Instructions/RType.h"
#include "Instructions/IType.h"
#include "Instructions/JType.h"

class SyntaxChecker : RType, IType, JType {
    private:      
        std::vector<std::string> splitInst(std::string);
    public:
        SyntaxChecker();
        ~SyntaxChecker();

        void checkSyntax(std::string);
        std::string checkInstType(std::string);
        bool checkBits(std::string) const;
};