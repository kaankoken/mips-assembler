#include "RType.h"
/**
 * Constructor of Rtype instructions
 * It also used for populating the data
*/
RType::RType() {
    rTypeInst.insert({"mflo", {7, 5, 5}});
    rTypeInst.insert({"mtlo", {8, 5, 5}});
}
/**
 * Descrutive of Rtype instructions
*/
RType::~RType() {
    rTypeInst.clear();
}
/**
 * @return unordered_map<string, tuple<int, int, int>>
 * It returns the whole instruction set that defined.
*/
std::unordered_map<std::string, std::tuple<int, int, int>> RType::getWholeInst() const {
    return rTypeInst;
}
/**
 * @param key -> string
 * @return tuple<int, int, int>
 * if instruction is found return tuple
 * else return -1, -1 ,-1
*/
std::tuple<int, int, int> RType::findInst(std::string key) const {
    auto instruction = rTypeInst.find(key);
    
    if (instruction == rTypeInst.end()) {
        std::cout << "Not Found" << std::endl;
        return std::make_tuple(-1, -1, -1);
    }
    else
        return std::make_tuple(std::get<0>(instruction->second), std::get<1>(instruction->second),
        std::get<2>(instruction->second));
}

std::string RType::fieldChecker(std::vector<std::string> inst) {
    if (inst.size() == 4) {
        std::string temp = inst.back();
        if (temp.at(0) > 96 && temp.at(0) < 123)
            return std::string("rs");
        else
            return std::string("shamt");
    }
    else {
        if (std::strcmp(inst.at(0).c_str(), "mflo") == 0 || std::strcmp(inst.at(0).c_str(), "mfhi") == 0)
            return std::string("rd");
        else
            return std::string("rs");
    }
}