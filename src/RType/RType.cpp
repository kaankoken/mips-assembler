#include "RType.h"
#include <iostream>

RType::RType() {
    rTypeInst.insert({"test", {5, 5, 5}});
    rTypeInst.insert({"test1", {6, 5, 5}});
}

RType::~RType() {
    rTypeInst.clear();
}

std::unordered_map<std::string, std::tuple<int, int, int>> RType::getWholeInst() const {
    return rTypeInst;
}

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