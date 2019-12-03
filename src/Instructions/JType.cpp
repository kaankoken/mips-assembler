#include "JType.h"
/**
 * Constructor of Jtype instructions
 * It also used for populating the data
*/
JType::JType() {
    jTypeInst.insert({"j", 2});
    jTypeInst.insert({"jal", 3});
}
/**
 * Descrutive of Jtype instructions
*/
JType::~JType() {
    jTypeInst.clear();
}
/**
 * @return unordered_map<string, int>
 * It returns the whole instruction set that defined.
*/
std::unordered_map<std::string, int> JType::getWholeInst() const {
    return jTypeInst;
}
/**
 * @param key -> string
 * @return int
 * if instruction is found return int
 * else return -1
*/
int JType::findInst(std::string key) const {
    auto instruction = jTypeInst.find(key);
    
    if (instruction == jTypeInst.end()) {
        std::cout << "Not Found" << std::endl;
        return -1;
    }
    else
        return instruction->second;
}