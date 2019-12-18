#include "BitConverter.h"

BitConverter::BitConverter() {}
BitConverter::~BitConverter() {}

void BitConverter::BinToDec() {

}

// void BitConverter::BinToHex() {
    // 
// }

void BitConverter::DecToBin(std::string instType, std::vector<std::string>inst,
  std::map<std::string, int> label, int pcCounter) {
    std::string result;
    int rs = 0, rt = 0, rd = 0, shamt = 0, func = 0, imm = 0;

    if (std::strcmp(instType.c_str(), "RType") == 0) {
        std::tuple instructions = RType::findInst(inst.at(0));
        
        //std::string instOrder = std::get<std::tuple_size<decltype(instructions)>::value - 1>(instructions);
        std::string instOrder = std::get<2>(instructions);
       
        //op
        result.append(BitConverter::bin(6, std::get<0>(instructions)));
        
        // registers
        std::vector<std::string>::iterator it = inst.begin() + 1;
        while (!instOrder.empty()) {
            std::string temp = splitOrder(&instOrder);
            if (std::strcmp(temp.c_str(), "rd") == 0)
                rd = Registers::findInst(*it);
            else if (std::strcmp(temp.c_str(), "rs") == 0)
                rs = Registers::findInst(*it);
            else if (std::strcmp(temp.c_str(), "rt") == 0)
                rt = Registers::findInst(*it);
            else {
                if (it->find("0x") == std::string::npos)
                    shamt = std::stoi(*it, 0, 10);
                else {
                    size_t pos = it->find("0x");
                    it->erase(it->begin(), it->begin() + pos + 2);
                    shamt = std::stoi(*it, 0, 16);
                }
            }
            it++;
        }

        if (shamt > 31) {
            std::cout << "Shamt value is bigger than 5 bits" << std::endl;
            exit(1);
        }
        if (shamt < 0) {
            std::cout << "Shamt value cannot be negative" << std::endl;
            exit(1);
        }

        //func
        func = std::get<1>(instructions);
        //finished inst
        result.append(BitConverter::bin(5, rs));
        result.append(BitConverter::bin(5, rt));
        result.append(BitConverter::bin(5, rd));
        result.append(BitConverter::bin(5, shamt));
        result.append(BitConverter::bin(6, func));
    }
    else if (std::strcmp(instType.c_str(), "IType") == 0) {
        std::tuple instructions = IType::findInst(inst.at(0));
        std::string instOrder = std::get<1>(instructions);

        result.append(BitConverter::bin(6, std::get<0>(instructions)));
        
        std::vector<std::string>::iterator it = inst.begin() + 1;
        std::map<std::string, int>::iterator mapIterator;
        while (!instOrder.empty()) {
            std::string temp = splitOrder(&instOrder);
            if (std::strcmp(temp.c_str(), "rs") == 0)
                rs = Registers::findInst(*it);
            else if (std::strcmp(temp.c_str(), "rt") == 0)
                rt = Registers::findInst(*it);
            else {
                if (label.size() > 0) {
                    if (label.find(*it + ":") != label.end()) {
                        mapIterator = label.find(*it + ":");
                        int diff = mapIterator->second - pcCounter;
                        diff /= 4;
                        *it = std::to_string(diff);
                    }
                }
                if (it->find("0x") == std::string::npos)
                    imm = std::stoi(*it, 0, 10);
                else {
                    size_t pos = it->find("0x");
                    it->erase(it->begin(), it->begin() + pos + 2);
                    imm = std::stoi(*it, 0, 16);
                }
            }
            it++;
        }
        /*
            bne s1 s2 label
            -------------------
            label:
        */
        if (imm > 32767 || imm < -32768) {
            std::cout << "Immediate value is bigger than 16 bits" << std::endl;
            exit(1);
        }

        result.append(BitConverter::bin(5, rs));
        result.append(BitConverter::bin(5, rt));
        result.append(BitConverter::bin(16, imm));
    }
    else {
    }
    std::cout << result << std::endl;
}
// 
// void BitConverter::DecToHex() {
// 
// }
// 
// void BitConverter::HexToBin() {
// 
// }
// 
// void BitConverter::HexToDec() {
    // 
// }

std::string BitConverter::bin(int size, int inst) {
    unsigned i;
    int temp = inst; 
    std::string result;
    if (inst < 0)
        temp *= -1;

    for (i = 1 << size - 1; i > 0; i = i / 2) 
        (temp & i)? result.append("1") : result.append("0");
    
    if (inst < 0) {
        for (i = result.length() - 1; i >= 0; i--)
            if (result[i] == '1')
                break;
        for (int k = i - 1; k >= 0; k--) {
            if (result[k] == '1') 
               result[k] = '0'; 
            else
                result[k] = '1'; 
        }
    }
    return result;
} 

std::string BitConverter::splitOrder(std::string *instOrder) {
    size_t pos = 0;
    std::string token, delimeter = " ";
    
    pos = instOrder->find(delimeter);

    if (instOrder->find(delimeter) != std::string::npos)
        token = instOrder->substr(0, pos);
    else {
        token.assign(*instOrder);
        instOrder->erase(0, instOrder->length());
    }
    instOrder->erase(0, pos + 1);
    return token;
}