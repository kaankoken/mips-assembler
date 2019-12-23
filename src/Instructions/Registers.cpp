#include "Registers.h"
/**
 * Constructor of Registers
 * It also used for populating the data
*/
Registers::Registers() {
    registers.insert({"zero", 0});
    registers.insert({"at", 1});    
    registers.insert({"v0", 2});
    registers.insert({"v1", 3});
    registers.insert({"a0", 4});
    registers.insert({"a1", 5});
    registers.insert({"a2", 6});
    registers.insert({"a3", 7});
    registers.insert({"t0", 8});
    registers.insert({"t1", 9});
    registers.insert({"t2", 10});
    registers.insert({"t3", 11});
    registers.insert({"t4", 12});
    registers.insert({"t5", 13});
    registers.insert({"t6", 14});
    registers.insert({"t7", 15});
    registers.insert({"t8", 24});
    registers.insert({"t9", 25});
    registers.insert({"s0", 16});
    registers.insert({"s1", 17});
    registers.insert({"s2", 18});
    registers.insert({"s3", 19});
    registers.insert({"s4", 20});
    registers.insert({"s5", 21});
    registers.insert({"s6", 22});
    registers.insert({"s7", 23});
    registers.insert({"k0", 26});
    registers.insert({"k1", 27});
    registers.insert({"gp", 28});
    registers.insert({"sp", 29});
    registers.insert({"fp", 30});
    registers.insert({"ra", 31});
}
/**
 * Descrutive of Registers instructions
*/
Registers::~Registers() {
    registers.clear();
}
/**
 * @return unordered_map<string, int>
 * It returns the whole registers that defined.
*/
std::unordered_map<std::string, int> Registers::getWholeInst() const {
    return registers;
}
/**
 * @param key -> string
 * @return int
 * if instruction is found return int
 * else return -1
*/
int Registers::findInst(std::string key) const {
    auto instruction = registers.find(key);
    
    if (instruction == registers.end()) {
        return -1;
    }
    else
        return instruction->second;
}