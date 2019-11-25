#include "IType.h"
/**
 * Constructor of Itype instructions
 * It also used for populating the data
*/
IType::IType() {
    iTypeInst.insert({"test", {5, 5}});
    iTypeInst.insert({"test1", {6, 5}});
}
/**
 * Descrutive of Itype instructions
*/
IType::~IType() {
    iTypeInst.clear();
}
/**
 * @return unordered_map<string, pair<int, int>>
 * It returns the whole instruction set that defined.
*/
std::unordered_map<std::string, std::pair<int, int>> IType::getWholeInst() const {
    return iTypeInst;
}
/**
 * @param key -> string
 * @return pair<int, int>
 * if instruction is found return pair
 * else return -1, -1
*/
std::pair<int, int> IType::findInst(std::string key) const {
    auto instruction = iTypeInst.find(key);
    
    if (instruction == iTypeInst.end()) {
        std::cout << "Not Found" << std::endl;
        return std::make_pair(-1, -1);
    }
    else
        return { std::get<0>(instruction->second), std::get<1>(instruction->second),
        };
}