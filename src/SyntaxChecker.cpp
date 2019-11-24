#include "SyntaxChecker.h"

SyntaxChecker::SyntaxChecker() : rTypeAreaLen { 5, 5, 5, 5, 6 },
                                 iTypeAreaLen { 5, 5, 16 },      
                                 jTypeAreaLen { 26 } {}
SyntaxChecker::~SyntaxChecker() {};

void SyntaxChecker::checkSyntax(std::string inst) {
    std::stack<char> temp;
    std::string result = checkInstType(inst);
    if (result.empty() == true)
        std::cout << "Error" << std::endl;
        //return NULL or false
    for (std::string::iterator it = inst.begin(); it != inst.end(); ++it) {
        if (temp.size() > 0)
            if (temp.top() == '(' && *it == ')')
                temp.push(*it);
        if (*it == '$' || *it == '(') {
            temp.push(*it);
        }
        else if (*it == ',' || *it == ')')
            temp.pop();
    }
    temp.pop();
    if (temp.size() > 0)
        std::cout << "Syntax Error" << std::endl;
    else
        std::cout << "No Error" << std::endl;
}

std::string SyntaxChecker::checkInstType(std:: string instType) {
    auto key = instType.substr(0, instType.find(' '));
    std::vector result = { RType::findInst(key), RType::findInst(key), RType::findInst(key)};
    // replace 2Rtype with IType and JType
    if (std::get<0>(result.at(0)) != -1)
        return std::string("RType");
    else if (std::get<0>(result.at(1)) != -1)
        return std::string("IType");
    else if (std::get<0>(result.at(2)) != -1)
        return std::string("JType");
    // else if (std::get<0>(result.at(3)) != -1)
    //     return std::string("file type");
    else
        return std::string("");
}

// bool SyntaxChecker::checkBits(std::string inst) const {
    // int n;
    // std::cout << std::bitset<sizeof(n) * 2 >(n).to_string();
// }
