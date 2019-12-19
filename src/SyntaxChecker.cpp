#include "SyntaxChecker.h"

SyntaxChecker::SyntaxChecker() {};
SyntaxChecker::~SyntaxChecker() {};

//Checks whether the entered syntax is correct or not
std::vector<std::string> SyntaxChecker::checkSyntax(std::string inst) {
    std::stack<char> temp;
    std::string result = checkInstType(inst);
    std::vector<std::string> text;

    if (result.length() == 0) {
        std::cout << "Instruction could not found" << std::endl;
        exit(1);
        return text;
    }

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
    if (temp.size() != 0)
        temp.pop();
    if (temp.size() > 0) {
        std::cout << "Syntax Error" << std::endl;
        exit(1);
    }

    text = splitInst(inst);
    
    return text;
}

//Checks the instruciton type is correct or not
std::string SyntaxChecker::checkInstType(std::string instType) {
    auto key = instType.substr(0, instType.find(' '));
    
    if (key[key.size() - 1] == ':') {
        size_t pos = instType.find(' ');
        key = instType.substr(pos, pos);
        key = key.substr(1, key.size());
        key = key.substr(0, key.find(' '));
    }

    std::tuple result = std::make_tuple(RType::findInst(key), IType::findInst(key), JType::findInst(key));

    if (std::get<0>(std::get<0>(result)) != -1)
        return std::string("RType");
    else if (std::get<0>(std::get<1>(result)) != -1)
        return std::string("IType");
    else if ((std::get<2>(result)) != -1)
        return std::string("JType");
    else return std::string("");
}
//Splits the instruction to parts
std::vector<std::string> SyntaxChecker::splitInst(std::string inst) {
    size_t pos = 0;
    std::string token, delimiter = " ";
    std::vector<std::string> temp;
    while ((pos = inst.find(delimiter)) != std::string::npos || inst.length() != 0) {
        if (inst.find(delimiter) != std::string::npos)
            token = inst.substr(0, pos);
        else {
            token.assign(inst);
            inst.erase(0, inst.length());
        }

        if (token.find(',') != std::string::npos)
            token.replace(token.find(','), 1, "");
        if (token.find('$') != std::string::npos)
            token.replace(token.find('$'), 1, "");
        if (token.find('(') != std::string::npos) {
            std::string temp2 = token.substr(0, token.find('('));
            if (temp2.find('x') != std::string::npos)
                temp2 = temp2.substr(temp2.find('x') + 1, temp2.length() - 1);
            temp.push_back(temp2);
            token = token.substr(token.find('(') + 1, token.find(')'));
            token.replace(token.find(')'), 1, "");
        }
        temp.push_back(token);
        inst.erase(0, pos + delimiter.length());
    }
    
    return temp;
}