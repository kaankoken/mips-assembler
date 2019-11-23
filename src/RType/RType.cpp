#include "RType.h"
/**
 * Constructor of Rtype instructions
 * It also used for populating the data
*/
RType::RType() {
    rTypeInst.insert({"test", {5, 5, 5}});
    rTypeInst.insert({"test1", {6, 5, 5}});
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
        return { std::get<0>(instruction->second), std::get<1>(instruction->second),
        std::get<2>(instruction->second) };
}