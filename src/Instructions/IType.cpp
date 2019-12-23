#include "IType.h"
/**
 * Constructor of Itype instructions
 * It also used for populating the data
*/
IType::IType() {
    iTypeInst.insert({"beq", {4,"rs rt imm"}});
    iTypeInst.insert({"bne", {5,"rs rt imm"}});
    iTypeInst.insert({"blez", {6,"rs imm"}});
    iTypeInst.insert({"bgtz", {7,"rs imm"}});
    iTypeInst.insert({"addi", {8,"rt rs imm"}});
    iTypeInst.insert({"addiu", {9,"rt rs imm"}});
    iTypeInst.insert({"slti", {10,"rt rs imm"}});
    iTypeInst.insert({"sltiu", {11,"rt rs imm"}});
    iTypeInst.insert({"andi", {12,"rt rs imm"}});
    iTypeInst.insert({"ori", {13,"rt rs imm"}});
    iTypeInst.insert({"xori", {14,"rt rs imm"}});
    iTypeInst.insert({"lui", {15,"rt imm"}});
    iTypeInst.insert({"lb", {32,"rt imm rs"}});
    iTypeInst.insert({"lh", {33,"rt imm rs"}});
    iTypeInst.insert({"lw", {35,"rt imm rs"}});
    iTypeInst.insert({"lbu", {36,"rt imm rs"}});
    iTypeInst.insert({"lhu", {37,"rt imm rs"}});
    iTypeInst.insert({"sb", {40,"rt imm rs"}});
    iTypeInst.insert({"sh", {41,"rt imm rs"}});
    iTypeInst.insert({"sw", {43,"rt imm rs"}});
}
/**
 * Descrutive of Itype instructions
*/
IType::~IType() {
    iTypeInst.clear();
}
/**
 * @return unordered_map<string, pair<int, std::string>>
 * It returns the whole instruction set that defined.
*/
std::unordered_map<std::string, std::pair<int, std::string>> IType::getWholeInst() const {
    return iTypeInst;
}
/**
 * @param key -> string
 * @return pair<int, std::string>
 * if instruction is found return pair
 * else return -1, NULL
*/
std::pair<int, std::string> IType::findInst(std::string key) const {
    auto instruction = iTypeInst.find(key);
    
    if (instruction == iTypeInst.end()) {
        return std::make_pair(-1, "");
    }
    else
        return std::make_pair(std::get<0>(instruction->second), std::get<1>(instruction->second));
}

void IType::setter(std::vector<std::string> temp) {
    iTypeInst.insert({ temp.at(1), {std::stoi(temp.at(2), 0, 10), temp.at(3)}});
}