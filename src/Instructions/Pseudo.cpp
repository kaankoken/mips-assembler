#include "Pseudo.h"

Pseudo::Pseudo() {
    pseudoInst.insert({"bgt", {{"slt $at, 2, 1"}, {"bne $at, $zero, 3"}}});
    pseudoInst.insert({"blt", {{"slt $at, 1, 2"}, {"bne $at, $zero, 3"}}});
    pseudoInst.insert({"bge", {{"slt $at, 1, 2"}, {"beq $at, $zero, 3"}}});
    pseudoInst.insert({"ble", {{"slt $at, 2, 1"}, {"beq $at, $zero, 3"}}});
    pseudoInst.insert({"bgtu", {{"sltu $at, $2, $1"}, {"bne $at, $zero, 3"}}});
    pseudoInst.insert({"beqz", {"beq 1, $zero, 2"}});
    pseudoInst.insert({"clear", {"or 1, $zero, $zero"}});
    pseudoInst.insert({"mul", {{"mult 2, 3"}, {"mflo 1"}}});
    pseudoInst.insert({"move", {"or 1, 2, $zero"}});
    pseudoInst.insert({"rem", {{"div 2, 3"}, {"mfhi 1"}}});
    pseudoInst.insert({"not", {"nor 1, 2, $zero"}});
    pseudoInst.insert({"nop ", {"sll $zero, $zero, 0"}});
}

Pseudo::~Pseudo() { pseudoInst.clear(); }

std::unordered_map<std::string, std::vector<std::string>> Pseudo::getWholeInst() const {
    return pseudoInst;
}

std::vector<std::string> Pseudo::convertInstructions(std::vector<std::string> instructionSet) {
    std::vector<std::string>::iterator it = instructionSet.begin();
    size_t pos = 1;
    size_t instSetPoint = 1;
    while (it != instructionSet.end()) {
        std::vector<std::string> temp = splitInst(*it);
        auto key = temp.at(0).find(':');
        std::string inst = temp.at(0);
 
        if (key < it->size())
            inst = temp.at(1);

        if (pseudoInst.find(inst) != pseudoInst.end()) {
            auto equivalentInst = pseudoInst.find(inst);
            std::vector<std::string>::iterator equIt = equivalentInst->second.begin();
            size_t size = 0;
            while (equivalentInst->second.end() != equIt) {
                std::string temp1 = equIt->c_str();

                if (key < it->size()) {
                    if (pos > 1)
                        pos = 1;
                    pos++;
                }
                if (equIt->find('1') != std::string::npos) {
                    temp1 = replaceStrings(temp.at(pos), temp1, temp1.find('1'));
                }
                pos++;

                if (equIt->find('2') != std::string::npos) {
                    temp1 = replaceStrings(temp.at(pos), temp1, temp1.find('2'));
                }
                pos++;

                if (equIt->find('3') != std::string::npos) {
                    temp1 = replaceStrings(temp.at(pos), temp1, temp1.find('3'));
                }
                pos++;
                if (key < it->size() && size < 1)
                   temp1 = temp.at(0) + " " + temp1;
                if (size < 1)
                    it->assign(temp1);
                else {
                    instructionSet.insert(instructionSet.begin() + instSetPoint, temp1);
                    it = instructionSet.begin() + instSetPoint;
                }

                equIt++;
                size++;
            }
            pos = 1;
        }
        instSetPoint++;
        it++;
    }

    return instructionSet;
}

std::vector<std::string> Pseudo::splitInst(std::string instruction) const {
    size_t pos = 0;
    std::vector<std::string> token;
    std::string delimeter = " ";

    while ((pos = instruction.find(delimeter)) != std::string::npos) {
        token.push_back(instruction.substr(0, pos));
        instruction.erase(0, pos + delimeter.length());
    }
    token.push_back(instruction);
    return token;
}

std::string Pseudo::replaceStrings(std::string src, std::string desc, size_t index) const {
    std::string temp, temp1;

    temp = desc.substr(0, index);
    if (index + 1 != desc.size()) {
        temp1 = desc.substr(index + 2, desc.size());
        if (src.find(',') == std::string::npos)
            src.push_back(',');
    }
    else
        if (src.find(',') != std::string::npos)
            src = src.substr(0, src.find(','));

    temp = temp + src + temp1;
    
    return temp;
}