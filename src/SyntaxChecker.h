#pragma once

#include <iostream>
#include <vector>
#include <stack> 
#include "Instructions/RType.h"
#include "Instructions/IType.h"
#include "Instructions/JType.h"
class SyntaxChecker : public RType, public IType, public JType {
    private:      
        std::vector<std::string> splitInst(std::string);
    public:
        SyntaxChecker();
        ~SyntaxChecker();

        std::vector<std::string> checkSyntax(std::string);
        std::string checkInstType(std::string);
        bool checkBits(std::string) const;
};