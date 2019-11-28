#include "JType.h"
/**
 * Constructor of Jtype instructions
 * It also used for populating the data
*/
JType::JType() {
    jTypeInst.insert({"test", {5, 5}});
    jTypeInst.insert({"test1", {6, 5}});
}
/**
 * Descrutive of Jtype instructions
*/
JType::~JType() {
    jTypeInst.clear();
}
/**
 * @return unordered_map<string, pair<int, int>>
 * It returns the whole instruction set that defined.
*/
std::unordered_map<std::string, std::pair<int, int>> JType::getWholeInst() const {
    return jTypeInst;
}
/**
 * @param key -> string
 * @return pair<int, int>
 * if instruction is found return tuple
 * else return -1, -1
*/
std::pair<int, int> JType::findInst(std::string key) const {
    auto instruction = jTypeInst.find(key);
    
    if (instruction == jTypeInst.end()) {
        std::cout << "Not Found" << std::endl;
        return std::make_pair(-1, -1);
    }
    else
        return { std::get<0>(instruction->second), std::get<1>(instruction->second) };
}