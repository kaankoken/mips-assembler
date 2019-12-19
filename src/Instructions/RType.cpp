#include "RType.h"
/**
 * Constructor of Rtype instructions
 * It also used for populating the data
*/
RType::RType() {
    rTypeInst.insert({"sll", {0, 0,"rd rt shamt"}});
    rTypeInst.insert({"srl", {0, 2,"rd rt shamt"}});
    rTypeInst.insert({"sra", {0, 3,"rd rt shamt"}});
    rTypeInst.insert({"sllv", {0, 4,"rd rt rs"}});
    rTypeInst.insert({"srlv", {0, 6,"rd rt rs"}});
    rTypeInst.insert({"srav", {0, 7,"rd rt rs"}});
    rTypeInst.insert({"jr", {0, 8,"rs"}});
    rTypeInst.insert({"jalr", {0, 9,"rd rs"}});
    rTypeInst.insert({"mfhi", {0, 16,"rd"}});
    rTypeInst.insert({"mthi", {0, 17,"rs"}});
    rTypeInst.insert({"mflo", {0, 18,"rd"}});
    rTypeInst.insert({"mtlo", {0, 19,"rs"}});
    rTypeInst.insert({"mult", {0, 24,"rs rt"}});
    rTypeInst.insert({"multu", {0, 25,"rs rt"}});
    rTypeInst.insert({"div", {0, 26,"rs rt"}});
    rTypeInst.insert({"divu", {0, 27,"rs rt"}});
    rTypeInst.insert({"add", {0, 32,"rd rs rt"}});
    rTypeInst.insert({"addu", {0, 33,"rd rs rt"}});
    rTypeInst.insert({"sub", {0, 34,"rd rs rt"}});
    rTypeInst.insert({"subu", {0, 35,"rd rs rt"}});
    rTypeInst.insert({"and", {0, 36,"rd rs rt"}});
    rTypeInst.insert({"or", {0, 37,"rd rs rt"}});
    rTypeInst.insert({"xor", {0, 38,"rd rs rt"}});
    rTypeInst.insert({"nor", {0, 39,"rd rs rt"}});
    rTypeInst.insert({"slt", {0, 42,"rd rs rt"}});
    rTypeInst.insert({"sltu", {0, 43,"rd rs rt"}});
}
/**
 * Descrutive of Rtype instructions
*/
RType::~RType() {
    rTypeInst.clear();
}
/**
 * @return unordered_map<string, tuple<int, int, std::string>>
 * It returns the whole instruction set that defined.
*/
std::unordered_map<std::string, std::tuple<int, int, std::string>> RType::getWholeInst() const {
    return rTypeInst;
}
/**
 * @param key -> string
 * @return tuple<int, int, std::string>
 * if instruction is found return tuple
 * else return -1, -1 , NULL
*/
std::tuple<int, int, std::string> RType::findInst(std::string key) const {
    auto instruction = rTypeInst.find(key);
    
    if (instruction == rTypeInst.end()) {
        return std::make_tuple(-1, -1, "");
    }
    else
        return std::make_tuple(std::get<0>(instruction->second), std::get<1>(instruction->second),
        std::get<2>(instruction->second));
}

// std::string RType::fieldChecker(std::vector<std::string> inst) {
    // if (inst.size() == 4) {
        // std::string temp = inst.back();
        // if (temp.at(0) > 96 && temp.at(0) < 123)
            // return std::string("rs");
        // else
            // return std::string("shamt");
    // }
    // else {
        // if (std::strcmp(inst.at(0).c_str(), "mflo") == 0 || std::strcmp(inst.at(0).c_str(), "mfhi") == 0)
            // return std::string("rd");
        // else
            // return std::string("rs");
    // }
// }