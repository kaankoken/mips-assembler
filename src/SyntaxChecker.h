#pragma once

#include <iostream>
#include <cstring>
#include <vector>
#include <bitset>
#include <stack> 
#include "RType/RType.h"
class SyntaxChecker : RType {
    private:
        int rTypeAreaLen[5];
        int iTypeAreaLen[3];
        int jTypeAreaLen;
        
        std::vector<std::string> splitInst(std::string);
    public:
        SyntaxChecker();
        ~SyntaxChecker();

        void checkSyntax(std::string);
        std::string checkInstType(std::string);
        bool checkBits(std::string) const;
};