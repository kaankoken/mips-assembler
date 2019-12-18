#pragma once

#include <bitset>
#include <iostream>
#include <vector>
#include <cstring>
#include <map>
#include "Instructions/RType.h"
#include "Instructions/IType.h"
#include "Instructions/JType.h"
#include "Instructions/Registers.h"

class BitConverter: RType, IType, JType, Registers {  
    private:
        std::string bin(int, int);
        std::string splitOrder(std::string *);

    public:
        BitConverter();
        ~BitConverter();

        void DecToBin(std::string, std::vector<std::string>, std::map<std::string, int>, int);
};