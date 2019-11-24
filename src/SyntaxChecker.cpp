#include "SyntaxChecker.h"

SyntaxChecker::SyntaxChecker() : rTypeAreaLen { 5, 5, 5, 5, 6 },
                                 iTypeAreaLen { 5, 5, 16 },      
                                 jTypeAreaLen { 26 } {}
SyntaxChecker::~SyntaxChecker() {};

void SyntaxChecker::checkSyntax(std::string inst) {
    std::string instType = checkInstType(inst);
    if (instType.compare("RType") == 0) {

    }
    else if (instType.compare("IType") == 0) {

    }
    else {
        
    }
}

std::string SyntaxChecker::checkInstType(std:: string instType) {
    auto key = instType.substr(0, instType.find(' '));
    std::vector result = { RType::findInst(key), RType::findInst(key), RType::findInst(key)};

    // replace 2Rtype with IType and JType
    if (std::get<0>(result.at(0)) != -1)
        return std::string("RType");
    else if (std::get<0>(result.at(1)) != -1)
        return std::string("IType");
    else
        return std::string("JType");
}

// bool SyntaxChecker::checkBits(std::string inst) const {
    // int n;
    // std::cout << std::bitset<sizeof(n) * 2 >(n).to_string();
// }