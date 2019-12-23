#pragma once

#include <bitset>
#include <iostream>
#include <vector>
#include <cstring>
#include <map>
#include "Instructions/Registers.h"
#include "SyntaxChecker.h"
class BitConverter: Registers, public SyntaxChecker {  
    private:
        std::string bin(int, int);
        std::string splitOrder(std::string *);

    public:
        BitConverter();
        ~BitConverter();

        std::string DecToBin(std::string, std::vector<std::string>, std::map<std::string, int>, int);
        std::vector<std::string> BinToHex(std::vector<std::string>);
};